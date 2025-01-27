/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 02:14:35 by caide-so          #+#    #+#             */
/*   Updated: 2025/01/27 00:15:03 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		count_args(char *cmd);
void	process_char(char *cmd, int idx[4], char ***args);
void	strip_quotes(char **token);

// Main parser of commands and its flags
// Splits a command string into arguments, handling quoted sections
// Uses idx[4] to track:
// idx[0] = Current character position (i)
// idx[1] = Start position of current token
// idx[2] = Quote Status (0/1)
// idx[3] = Current index in the args array
char	**parse_args(char *cmd)
{
	char	**args;
	int		idx[4];

	idx[0] = 0;
	idx[1] = 0;
	idx[2] = 0;
	idx[3] = 0;
	args = ft_calloc(count_args(cmd) + 1, sizeof(char *));
	if (!args)
		return (NULL);
	while (cmd[idx[0]])
	{
		process_char(cmd, idx, &args);
		idx[0]++;
	}
	args[idx[3]] = ft_substr(cmd, idx[1], idx[0] - idx[1]);
	strip_quotes(&args[idx[3]]);
	return (args);
}

// Counts tokens in command strings, ignoring spaces inside quotes
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

// Processes individual characters to build argument tokens
// - Toggles quote status when encountering ' or "
// - Splits tokens at unquoted spaces
// - Automatically strips quotes from completed tokens
// idx[0] = current position (i)
// idx[1] = start position
// idx[2] = in_quote status
// idx[3] = array index (arr_idx)
void	process_char(char *cmd, int idx[4], char ***args)
{
	if (cmd[idx[0]] == '\'' || cmd[idx[0]] == '"')
		idx[2] = !idx[2];
	else if (cmd[idx[0]] == ' ' && !idx[2])
	{
		(*args)[idx[3]] = ft_substr(cmd, idx[1], idx[0] - idx[1]);
		strip_quotes(&(*args)[idx[3]++]);
		idx[1] = idx[0] + 1;
	}
}

// Checks if first and last characters are matching quotes
// Creates a new substring excluding the quotes
// Frees the original quoted string
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
