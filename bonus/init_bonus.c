/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 02:13:47 by caide-so          #+#    #+#             */
/*   Updated: 2025/01/26 20:23:25 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	parse_commands(t_pipex *pipex, int argc, char **argv);

t_pipex	*init_pipex(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (pipex == NULL)
		error(2, NULL);
	ft_bzero(pipex, sizeof(t_pipex));
	pipex->heredoc = (ft_strncmp(argv[1], "here_doc", 8) == 0);
	pipex->envp = envp;
	pipex->infile = argv[1];
	pipex->outfile = argv[argc - 1];
	if (!pipex->heredoc && access(pipex->infile, R_OK) != 0)
		error(5, pipex);
	parse_commands(pipex, argc, argv);
	return (pipex);
}

void	parse_commands(t_pipex *pipex, int argc, char **argv)
{
	int		start;
	int		i;

	start = 2 + pipex->heredoc;
	pipex->cmd_count = argc - start - 1;
	pipex->cmd_args = ft_calloc(pipex->cmd_count + 1, sizeof(char **));
	pipex->cmd_paths = ft_calloc(pipex->cmd_count + 1, sizeof(char *));
	if (!pipex->cmd_args || !pipex->cmd_paths)
		error(2, pipex);
	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->cmd_args[i] = parse_args(argv[start + i]);
		if (!pipex->cmd_args[i] || !pipex->cmd_args[i][0])
			error(3, pipex);
		pipex->cmd_paths[i] = find_path(pipex->cmd_args[i][0], pipex->envp);
		if (!pipex->cmd_paths[i])
			error(3, pipex);
		i++;
	}
}
