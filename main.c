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

int	main(int argc, char **argv, char **envp)
{
	int	fd;
	char	buffer[1024];
	ssize_t	bytes_read;

	if (argc != 2)
	{
		ft_printf("Usage: ./pipex <filename>\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	while ((bytes_read = read(fd, buffer, 1023)) > 0)
	{
		buffer[bytes_read] = '\0';
		write(1, buffer, bytes_read);
	}
	if (bytes_read == -1)
		perror("Error reading file");
	close(fd);

	char	*cmd = "/bin/ls";
	char	*args[] = {cmd, "-l", NULL};

	if (execve(cmd, args, envp) == -1)
	{
		perror("Error executing command");
		return (1);
	}
	return (0);
}
