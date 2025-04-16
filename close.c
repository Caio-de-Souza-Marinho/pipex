/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 02:15:51 by caide-so          #+#    #+#             */
/*   Updated: 2025/01/27 00:16:51 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Frees all dynamically allocated memory in the t_pipex struct.
// 1. Frees cmd_args (a 3D array) and cmd_paths (a 2D array).
// 2. Releases the struct itself.
// Note: Called during error handling and program termination.
void	free_pipex(t_pipex *pipex)
{
	if (pipex == NULL)
		return ;
	if (pipex->cmd_args)
		free_split_split(pipex->cmd_args);
	if (pipex->cmd_paths)
		free_split(pipex->cmd_paths);
	free(pipex);
}

// Frees a 2D array of strings.
// 1. Iterates through each string in the array.
// 2. Frees individual strings and the array itself.
void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// Frees a 3d array of strings.
// 1. Iterates through each sub-array.
// 2. Frees nested strings and sub-arrays.
void	free_split_split(char ***arr)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			free(arr[i][j]);
			j++;
		}
		free(arr[i]);
		i++;
	}
	free(arr);
}
