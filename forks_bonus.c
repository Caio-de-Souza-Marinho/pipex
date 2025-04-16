/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:42:57 by caide-so          #+#    #+#             */
/*   Updated: 2025/01/26 23:39:54 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_child(t_pipex *pipex, int idx, int prev_pipe, int pipe_fd[2]);
void	handle_parent(t_pipex *pipex, int idx, int *prev_pipe, int pipe_fd[2]);
void	redirect_output(t_pipex *pipex, int idx);
void	close_pipes(int prev_pipe, int pipe_fd[2]);

// Executes all commands in a pipeline with proper input/output redirection.
// 1. Opens the input or uses heredoc_fd in heredoc mode.
// 2. For each command:
// - Creates pipes (except for the last command).
// - Forks child processes to execute commands.
// - Redirects stdin/stdout using dup2.
// 3. Waits for all child processes to complete.
// Note: The last command writes to outfile instead of a pipe.
void	exec_pipeline(t_pipex *pipex)
{
	int	prev_pipe;
	int	i;
	int	pipe_fd[2];

	if (pipex->heredoc)
		prev_pipe = pipex->heredoc_fd;
	else
		prev_pipe = open(pipex->infile, O_RDONLY);
	if (prev_pipe < 0 && !pipex->heredoc)
		error(5, pipex);
	i = 0;
	while (i < pipex->cmd_count)
	{
		if (i < pipex->cmd_count - 1 && pipe(pipe_fd) < 0)
			error(7, pipex);
		exec_child(pipex, i, prev_pipe, pipe_fd);
		handle_parent(pipex, i, &prev_pipe, pipe_fd);
		i++;
	}
	close(prev_pipe);
	while (wait(NULL) > 0)
		;
}

// Handles child process setup and command execution.
// 1. Forks a new process.
// 2. Redirects stdin from prev_pipe and stdout to pipe_fd[1] (or outfile).
// 3. Executes the command via execve().
// Note: Terminates the child process on failure.
void	exec_child(t_pipex *pipex, int idx, int prev_pipe, int pipe_fd[2])
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error(8, pipex);
	if (pid == 0)
	{
		dup2(prev_pipe, STDIN_FILENO);
		if (idx < pipex->cmd_count - 1)
			dup2(pipe_fd[1], STDOUT_FILENO);
		else
			redirect_output(pipex, idx);
		close_pipes(prev_pipe, pipe_fd);
		execve(pipex->cmd_paths[idx], pipex->cmd_args[idx], pipex->envp);
	}
}

// Manages pipe file descriptors in the parent process.
// 1. Closes the previous pipe input.
// 2. Updates prev_pipe to the current pipe's read end for the next command.
// Note: Ensures unused pipes are closed to prevent leaks.
void	handle_parent(t_pipex *pipex, int idx, int *prev_pipe, int pipe_fd[2])
{
	(void)pipex;
	close(*prev_pipe);
	if (idx < pipex->cmd_count - 1)
		*prev_pipe = pipe_fd[0];
	close(pipe_fd[1]);
}

// Redirects stdout of the last command to the output file.
// 1. Opens outfile with O_APPEND in heredoc mode or O_TRUNC otherwise.
// 2. Uses dup2 to redirect output to the file descriptor.
// Note: Ensures the output file is created with 0644 permissions.
void	redirect_output(t_pipex *pipex, int idx)
{
	int	out_flags;
	int	out_fd;

	(void)idx;
	if (pipex->heredoc)
		out_flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		out_flags = O_WRONLY | O_CREAT | O_TRUNC;
	out_fd = open(pipex->outfile, out_flags, 0644);
	if (out_fd < 0)
		error(6, pipex);
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
}

// Closes pipe file descriptors after redirection.
// 1. Closes prev_pipe (if not stdin).
// 2. Closes both ends of the current pipe.
void	close_pipes(int prev_pipe, int pipe_fd[2])
{
	if (prev_pipe != STDIN_FILENO)
		close(prev_pipe);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
