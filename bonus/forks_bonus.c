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

/*
void	give_birth(t_pipex *pipex)
{
	int	pipe_fd[2];
	int	pid1;
	int	pid2;

	// Create pipe
	if (pipe(pipe_fd) == -1)
		error(7, pipex);
	// Fork the first child
	pid1 = fork();
	if (pid1 < 0)
		error(8, pipex);
	if (pid1 == 0)
		first_child_process(pipe_fd, pipex);
	// Fork the second child
	pid2 = fork();
	if (pid2 < 0)
		error(8, pipex);
	if (pid2 == 0)
		second_child_process(pipe_fd, pipex);
	// Close pipes
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	// The parent will wait for the second child process later
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	first_child_process(int pipe_fd[2], t_pipex *pipex)
{
	int	infile_fd;

	infile_fd = open(pipex->infile, O_RDONLY);
	if (infile_fd < 0)
		error(5, pipex);
	// Redirect stdin to the input file
	if (dup2(infile_fd, STDIN_FILENO) < 0)
		error(9, pipex);
	// Close the original file descriptor
	close(infile_fd);
	// Redirect stdout to the write-end of the pipe
	if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
		error(10, pipex);
	// Close unused read-end of the pipe
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	// Execute the first command
	if (execve(pipex->cmd1_path, pipex->cmd1_args, pipex->envp) < 0)
		error(11, pipex);
}

void	second_child_process(int pipe_fd[2], t_pipex *pipex)
{
	int	outfile_fd;

	outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
		error(6, pipex);
	// Redirect stdin to the read-end of the pipe
	if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
		error(9, pipex);
	// Redirect stdout to the write-end of the pipe
	if (dup2(outfile_fd, STDOUT_FILENO) < 0)
		error(10, pipex);
	// Close unused read-end of the pipe
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	// Close the original file descriptor
	close(outfile_fd);
	// Execute the first command
	if (execve(pipex->cmd2_path, pipex->cmd2_args, pipex->envp) < 0)
		error(11, pipex);
}
*/
