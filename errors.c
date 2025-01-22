/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 20:47:05 by caide-so          #+#    #+#             */
/*   Updated: 2025/01/19 20:58:45 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	error(int exit_code, t_pipex *pipex)
{
	print_pipex(pipex);
	if (pipex != NULL)
		free_pipex(pipex);
	if (exit_code == 1)
		ft_printf("Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n");
	else if (exit_code == 2)
		ft_printf("Cannot initialize pipex\n");
	else if (exit_code == 3)
		ft_printf("Cannot find commands\n");
	else if (exit_code == 5)
		ft_printf("Infile not found\n");
	else if (exit_code == 6)
		ft_printf("Failed to create outfile\n");
	else if (exit_code == 7)
		ft_printf("Error creating pipes\n");
	else if (exit_code == 8)
		ft_printf("Error during fork\n");
	else if (exit_code == 9)
		ft_printf("Error redirecting input file\n");
	else if (exit_code == 10)
		ft_printf("Error redirecting write end\n");
	else if (exit_code == 11)
		ft_printf("Error executing first command\n");
	exit(exit_code);
}
