/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:17:47 by caide-so          #+#    #+#             */
/*   Updated: 2025/01/26 20:18:41 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_path_env(char **envp);
char	*validate_command_path(char **paths, char *cmd);
char	*split_and_join_path(char *directory, char *cmd);
char	*validate_full_path(char *cmd);

// Get the PATH environment variable
// Split PATH into directoreis
char	*find_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;

	if (*cmd == '/')
		return (validate_full_path(cmd));
	path_env = get_path_env(envp);
	if (path_env == NULL || cmd == NULL || *cmd == '\0')
		return (NULL);
	paths = ft_split(path_env, ':');
	if (paths == NULL)
		error(4, NULL);
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

char	*validate_full_path(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
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
		if (access(full_path, F_OK | X_OK) == 0)
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
		error(4, NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_path);
}
