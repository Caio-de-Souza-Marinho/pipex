/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 21:19:47 by caide-so          #+#    #+#             */
/*   Updated: 2025/01/26 23:56:01 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Entry point of the program.
// 1. Validates command-line arguments.
// 2. Initializes pipex and handles heredoc.
// 3. Executes the pipeline and cleans up resources.
int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc < 5 + (ft_strncmp(argv[1], "here_doc", 8) == 0))
		error(1, NULL);
	pipex = init_pipex(argc, argv, envp);
	if (pipex->heredoc)
		handle_heredoc(pipex, argv[2]);
	exec_pipeline(pipex);
	free_pipex(pipex);
	return (0);
}

/*
//============================= DEBUG FUNCTIONS ===============================
void	print_pipex(t_pipex *pipex)
{
	ft_printf("==================START PIPEX STRUCT==================\n");
	ft_printf("infile - %s\n", pipex->infile);
	ft_printf("cmd count - %d\n", pipex->cmd_count);
	ft_printf("heredoc - %d\n", pipex->heredoc);
	print_envp(pipex->cmd_paths, "CMD PATHS");
	print_cmd_args(pipex->cmd_args, "CMD ARGS");
	ft_printf("outfile - %s\n", pipex->outfile);
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

void	print_cmd_args(char ***cmds, char *s)
{
	int	i;
	int	j;

	ft_printf("PRINT %s STRINGS\n", s);
	i = 0;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i][j])
		{
			ft_printf("%s\n", cmds[i][j]);
			j++;
		}
		i++;
	}
}
*/
