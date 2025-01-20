/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 02:14:35 by caide-so          #+#    #+#             */
/*   Updated: 2025/01/20 02:25:56 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path_env(char **envp);
char	*validate_command_path(char **paths, char *cmd);
char	*split_and_join_path(char *directory, char *cmd);

// Get the PATH environment variable
// Split PATH into directoreis
char	*find_command_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;

	path_env = get_path_env(envp);
	if (path_env == NULL || cmd == NULL || *cmd == '\0')
		return (NULL);
	paths = ft_split(path_env, ':');
	if (paths == NULL)
		error(4);
	return (validate_command_path(paths, cmd));
}

// Find PATH variable in envp
char	*get_path_env(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*validate_command_path(char **paths, char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = split_and_join_path(paths[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

char	*split_and_join_path(char *directory, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(directory, "/");
	if (tmp == NULL)
		error(4);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_path);
}
