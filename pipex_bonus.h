/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 21:22:59 by caide-so          #+#    #+#             */
/*   Updated: 2025/01/22 22:07:31 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/include/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	char	*infile;
	char	**envp;
	char	**cmd1_args;
	char	**cmd2_args;
	char	*cmd1_path;
	char	*cmd2_path;
	char	*outfile;
}	t_pipex;

// errors
int		error(int exit_code, t_pipex *pipex);

// init struct
t_pipex	*init_pipex(char **argv, char **envp);

// parse args
char	*find_command_path(char *cmd, char **envp);

// close / free
void	free_pipex(t_pipex *pipex);
void	free_split(char **arr);

// forks
void	give_birth(t_pipex *pipex);
void	first_child_process(int pipe_fd[2], t_pipex *pipex);
void	second_child_process(int pipe_fd[2], t_pipex *pipex);

// debug
void	print_pipex(t_pipex *pipex);
void	print_envp(char **envp, char *s);

#endif
