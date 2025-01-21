/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 21:19:47 by caide-so          #+#    #+#             */
/*   Updated: 2025/01/20 02:32:33 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_pipex(t_pipex *pipex);
void	print_envp(char **envp, char *s);

void	give_birth(t_pipex *pipex);
void	first_child_process(int pipe_fd[2], t_pipex *pipex);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc != 5)
		error(1);
	if (envp == NULL || *envp == NULL)
		error(3);
	pipex = init_pipex(argv, envp);
	/*
	print_envp(envp, "envp");
	print_pipex(pipex);
	*/
	give_birth(pipex);
	free_pipex(pipex);
	return (0);
}

void	give_birth(t_pipex *pipex)
{
	int	pipe_fd[2];
	int	pid;

	// Create pipe
	if (pipe(pipe_fd) == -1)
		error(7);
	// Fork the first child process
	pid = fork();
	if (pid < 0)
		error(8);
	if (pid == 0)
	{
		// Child process: Run cmd1
		first_child_process(pipe_fd, pipex);
	}
	// Parent process: Continue to set up the second child :TODO
	close(pipe_fd[1]);
	// The parent will wait for the second child process later
}

void	first_child_process(int pipe_fd[2], t_pipex *pipex)
{
	// Open the infile
	int	infile_fd;

	infile_fd = open(pipex->infile, O_RDONLY);
	if (infile_fd < 0)
		error(5);
	// Redirect stdin to the input file (using dup2)
	if (dup2(infile_fd, STDIN_FILENO) < 0)
		error(9);
	// Close the original file descriptor
	close(infile_fd);
	// Redirect stdout to the write-end of the pipe
	if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
		error(10);
	// Close unused read-end of the pipe
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	// Execute the first command
	if (execve(pipex->cmd1_path, pipex->cmd1_args, pipex->envp) < 0)
		error(11);
}

void	print_pipex(t_pipex *pipex)
{
	ft_printf("==================START PIPEX STRUCT==================\n");
	ft_printf("%s\n", pipex->infile);
	ft_printf("%s\n", pipex->outfile);
	print_envp(pipex->cmd1_args, "cmd1_args");
	print_envp(pipex->cmd2_args, "cmd2_args");
	ft_printf("%s\n", pipex->cmd1_path);
	ft_printf("%s\n", pipex->cmd2_path);
}

void	print_envp(char **envp, char *s)
{
	int	i;

	ft_printf("PRINT %s STRINGS\n", s);
	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
}

