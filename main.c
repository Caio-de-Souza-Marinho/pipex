/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 21:19:47 by caide-so          #+#    #+#             */
/*   Updated: 2025/01/16 22:01:28 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main()
{
	int pid;

	pid = fork();

	if (pid < 0)
	{
		// Fork failed
		perror("fork");
		return (1);
	}
	else if (pid == 0)
		printf("This is the child process with PID %d\n", getpid());
	else
		printf("This is the parent process with PID %d\n", getpid());
}
/*
int	main(int argc, char **argv, char **envp)
{
	int	pipe_fd[2];
	int	pid;

	if (argc != 2)
	{
		ft_printf("Usage: ./pipex <filename>\n");
		return (1);
	}
	if (pipe(pipe_fd) == -1) // Create a pipe
	{
		perror("Error creating pipe");
		return (1);
	}
	pid = fork(); // Create a child process
	if (pid == -1)
	{
		perror("Error forking process");
		return (1);
	}
	if (pid == 0) // Child process
	{
		// Redirect sdtout to the write end of the pipe
		dup2(pipe_fd[1], 1);
		close(pipe_fd[0]); // Close unused read end of the pipe
		close(pipe_fd[1]);

		// Excecute "cat file.txt"
		char *cmd1 = "/bin/cat";
		char *args1[] = {cmd1, argv[1], NULL};
		if (execve(cmd1, args1, envp) == -1)
		{
			perror("Error executing cat");
			exit(1);
		}
	}
	else // Parent process
	{
		// Redirect stdin to the read end of the pipe
		dup2(pipe_fd[0], 0);
		close(pipe_fd[1]); // Close unused write end of the pipe
		close(pipe_fd[0]);
	
		// Execute "wc -l"
		char *cmd2 = "/usr/bin/wc";
		char *args2[] = {cmd2, "-l", NULL};
		if (execve(cmd2, args2, envp) == -1)
		{
			perror("Error executing wc");	
			exit(1);
		}
	}
	

	return (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
	int pipefd[2]; // Array to hold pipe file descriptors
	pid_t pid;     // Process ID
	char buffer[128];

	// Step 1: Create a pipe
	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	// Step 2: Fork a child process
	pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0) {
		// Child process

		// Step 3: Close the write end of the pipe in the child
		close(pipefd[1]);

		// Step 4: Read data from the pipe
		read(pipefd[0], buffer, sizeof(buffer));
		printf("Child received: %s\n", buffer);

		// Step 5: Close the read end of the pipe
		close(pipefd[0]);
		exit(EXIT_SUCCESS);
	} else {
		// Parent process

		// Step 6: Close the read end of the pipe in the parent
		close(pipefd[0]);

		// Step 7: Write data to the pipe
		const char *message = "Hello from parent!";
		write(pipefd[1], message, strlen(message) + 1); // Include null terminator

		// Step 8: Close the write end of the pipe
		close(pipefd[1]);

		// Step 9: Wait for child to finish
		wait(NULL);
	}

	return 0;
}
*/
