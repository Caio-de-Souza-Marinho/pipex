/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 21:22:59 by caide-so          #+#    #+#             */
/*   Updated: 2025/01/27 00:13:31 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/include/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

// Represents the core configuration and data for the pipex pipeline.
// Members:
// infile: Input file name (or "here_doc" if heredoce mode is active).
// envp: Environment variables (used to locate commands paths).
// cmd_count: Number of commands to execute in the pipeline.
// heredoc: Flag (1/0) indicating if heredoc mode is active.
// heredoc_fd: File descriptor for the heredoc temporary input.
// cmd_args: 2D array of parsed command arguments (e.g., {"ls", "-l", NULL}).
// cmd_paths: Array of resolved executable paths for each command.
// outfile: Output file name.
// Note: heredoc_fd is only valid if heredoc is set to 1.
// Note: cmd_args and cmd_paths must be freed after execution.
typedef struct s_pipex
{
	char	*infile;
	char	**envp;
	int		cmd_count;
	int		heredoc;
	int		heredoc_fd;
	char	***cmd_args;
	char	**cmd_paths;
	char	*outfile;
}	t_pipex;

// errors
int		error(int exit_code, t_pipex *pipex);

// init struct
t_pipex	*init_pipex(int argc, char **argv, char **envp);

// find command paths
char	*find_path(char *cmd, char **envp);

// close / free
void	free_split(char **arr);
void	free_split_split(char ***arr);
void	free_pipex(t_pipex *pipex);

// forks
void	exec_pipeline(t_pipex *pipex);

// parse command strings
char	**parse_args(char *cmd);

// debug
void	print_pipex(t_pipex *pipex);
void	print_envp(char **envp, char *s);

// here doc handling
void	handle_heredoc(t_pipex *pipex, char *limiter);

#endif
