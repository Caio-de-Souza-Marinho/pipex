/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 02:14:35 by caide-so          #+#    #+#             */
/*   Updated: 2025/01/26 22:49:25 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int		count_args(char *cmd);
void	process_char(char *cmd, int idx[4], char ***args);
void	strip_quotes(char **token);

// Splits a command string into tokens, handling quoted arguments.
// Uses idx[4] to track:
// idx[0] = Current character position (i).
// idx[1] = Start position of current token.
// idx[2] = Quote Status (0/1).
// idx[3] = Current index in the args array.
// 1. Uses count_args to determine the number of tokens, ignoring spaces inside
// quotes.
// 2. Iterates through the command string to extract tokens.
// 3. Calls strip_quotes to remove enclosing quotes from each token.
// Note: Supports both single and double quotes.
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

// Counts the number of tokens in a command string, ignoring spaces inside
// quotes.
// 1. Iterates through the command string.
// 2. Tracks quote status (single ' or double ").
// 3. Increments the token count for each unquoted space.
// 4. Returns the total token count +1 to account for the final token.
// Note: Used by parse_args to preallocate memory for argument arrays.
// Note: Spaces within quotes are not treated as token separators.
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

// Processes individual characters in a command string to build argument tokens
// handling quoted sections.
// 1. Toggles quote status when encountering ' or ".
// 2. Splits tokens at unquoted spaces.
// 3. Automatically strips quotes from completed tokens.
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

// Removes enclosing quotes from a token (e.g., "'hello'" -> "hello").
// 1. Checks if the first and last characters are matching quotes.
// 2. Creates a new substring excluding the quotes.
// 3. Frees the original quotes string.
// Note: Only removes quotes if they fully enclose the token.
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
