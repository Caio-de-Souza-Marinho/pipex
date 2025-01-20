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

int	error(int exit_code)
{
	if (exit_code == 1)
		ft_printf("Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n");
	else if (exit_code == 2)
		ft_printf("Cannot initialize pipex\n");
	else if (exit_code == 3)
		ft_printf("Cannot find commands\n");
	else if (exit_code == 4)
		ft_printf("Memory allocation failed while building the command path\n");
	else if (exit_code == 5)
		ft_printf("Infile not found\n");
	else if (exit_code == 6)
		ft_printf("Failed to create outfile\n");
	exit(exit_code);
}
