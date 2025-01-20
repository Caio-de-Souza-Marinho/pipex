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

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc != 5)
		error(1);
	if (envp == NULL || *envp == NULL)
		error(3);
	pipex = init_pipex(argv, envp);
	//print_envp(envp, "envp");
	print_pipex(pipex);
	free_pipex(pipex);
	return (0);
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
