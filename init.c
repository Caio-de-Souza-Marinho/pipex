/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 02:13:47 by caide-so          #+#    #+#             */
/*   Updated: 2025/01/20 02:14:14 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*init_pipex(char **argv, char **envp)
{
	t_pipex	*pipex;
	int		fd;

	pipex = malloc(sizeof(t_pipex));
	if (pipex == NULL)
		error(2, NULL);
	ft_bzero(pipex, sizeof(t_pipex));
	pipex->infile = argv[1];
	if (access(pipex->infile, R_OK) != 0)
		error(5, pipex);
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error(6, pipex);
	close(fd);
	pipex->outfile = argv[4];
	pipex->envp = envp;
	if (!argv[2] || !argv[3] || *argv[2] == '\0' || *argv[3] == '\0')
		error(3, pipex);
	pipex->cmd1_args = ft_split(argv[2], ' ');
	pipex->cmd2_args = ft_split(argv[3], ' ');
	pipex->cmd1_path = find_command_path(pipex->cmd1_args[0], envp);
	pipex->cmd2_path = find_command_path(pipex->cmd2_args[0], envp);
	if (pipex->cmd1_path == NULL || pipex->cmd2_path == NULL)
		error(3, pipex);
	return (pipex);
}
