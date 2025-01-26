/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:42:57 by caide-so          #+#    #+#             */
/*   Updated: 2025/01/22 22:07:31 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_child(t_pipex *pipex, int idx, int prev_pipe, int pipe_fd[2]);
void	handle_parent(t_pipex *pipex, int idx, int *prev_pipe, int pipe_fd[2]);
void	redirect_output(t_pipex *pipex, int idx);
void	close_pipes(int prev_pipe, int pipe_fd[2]);

// Main pipeline execution controller
void	exec_pipeline(t_pipex *pipex)
{
	int	prev_pipe;
	int	i;
	int	pipe_fd[2];

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

// Handle child process execution logic
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

// Manages parent process pipe handling
void	handle_parent(t_pipex *pipex, int idx, int *prev_pipe, int pipe_fd[2])
{
	(void)pipex;
	close(*prev_pipe);
	if (idx < pipex->cmd_count - 1)
		*prev_pipe = pipe_fd[0];
	close(pipe_fd[1]);
}

// Handles output redirection for last command
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

// Cleanup function for pipe file descriptors
void	close_pipes(int prev_pipe, int pipe_fd[2])
{
	if (prev_pipe != STDIN_FILENO)
		close(prev_pipe);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
