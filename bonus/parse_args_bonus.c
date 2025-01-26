/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 02:14:35 by caide-so          #+#    #+#             */
/*   Updated: 2025/01/26 20:18:29 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	count_args(char *cmd);
void	strip_quotes(char **token);

// Main parser of commands and its flags
char	**parse_args(char *cmd)
{
	char	**args;
	int		i;
	int		start;
	int		in_quote;
	int		arr_idx;

	args = ft_calloc(count_args(cmd) + 1, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	start = 0;
	in_quote = 0;
	arr_idx = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			in_quote = !in_quote;
		else if (cmd[i] == ' ' && !in_quote)
		{
			args[arr_idx] = ft_substr(cmd, start, i - start);
			strip_quotes(&args[arr_idx]);
			arr_idx++;
			start = i + 1;
		}
		i++;
	}
	args[arr_idx] = ft_substr(cmd, start, i - start);
	strip_quotes(&args[arr_idx]);
	return (args);
}

// Helper function to count arguments (accounts for quotes)
int	count_args(char *cmd)
{
	int	count;
	int	in_quote;

	count = 0;
	in_quote = 0;
	while (*cmd)
	{
		if (*cmd == '\'' || *cmd == '"')
			in_quote = !in_quote;
		else if (*cmd == ' ' && !in_quote)
			count++;
		cmd++;
	}
	return (count + 1);
}

void	strip_quotes(char **token)
{
	char	*str;
	size_t	len;

	str = *token;
	if (!str)
		return ;
	len = ft_strlen(str);
	if (len < 2)
		return ;
	if ((str[0] == '\'' && str[len - 1] == '\'')
		|| (str[0] == '"' && str[len - 1] == '"'))
	{
		*token = ft_substr(str, 1, len - 2);
		free(str);
	}
}
