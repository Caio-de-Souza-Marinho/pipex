/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 23:49:41 by caide-so          #+#    #+#             */
/*   Updated: 2025/01/27 00:12:07 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_heredoc(t_pipex *pipex, char *limiter)
{
	int		pipe_fd[2];
	char	*line;
	int		limiter_len;

	if (pipe(pipe_fd) < 0)
		error(7, pipex);
	limiter_len = ft_strlen(limiter);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line || (ft_strncmp(line, limiter, limiter_len) == 0
				&& line[limiter_len] == '\n' && line[limiter_len + 1] == 0))
			break ;
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(pipe_fd[1]);
	pipex->heredoc_fd = pipe_fd[0];
}
