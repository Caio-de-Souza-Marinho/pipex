/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 02:13:47 by caide-so          #+#    #+#             */
/*   Updated: 2025/01/27 00:14:42 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parse_commands(t_pipex *pipex, int argc, char **argv);

// Initializes the t_pipex struct with command-line arguments and environment
// variables.
// 1. Allocates memory for the struct and initializes it to zero.
// 2. Detects heredoc mode if the first argument is "here_doc".
// 3. Sets input/output file names and validates input file access
// (non_heredoc mode).
// 4. Parses command arguments and resolves executables paths.
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

// Parses command-line arguments into executable commands.
// 1. Allocates memory for cmd_args and cmd_paths.
// 2. Uses parse_args to split command strings into tokens.
// 3. Resolves executable paths via find_path.
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
