/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:32:41 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/16 13:03:19 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	if_quote_close(char *line)
{
	int		i;
	int		in_quote;
	char	quote_char;

	i = 0;
	in_quote = 0;
	quote_char = '\0';
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"') && in_quote == 0)
		{
			in_quote = 1;
			quote_char = line[i];
		}
		else if (line[i] == quote_char && in_quote == 1)
			in_quote = 0;
		i++;
	}
	if (in_quote == 0)
		return (FALSE);
	return (TRUE);
}

char	if_in_quote(char *line, size_t *i)
{
	size_t	j;
	char	quote_char;

	j = 0;
	quote_char = '\0';
	while (j < *i)
	{
		if ((line[j] == '\'' || line[j] == '"') && quote_char == '\0')	
			quote_char = line[j];
		else if (line[j] == quote_char)
			quote_char = '\0';
		j++;
	}
	return (quote_char);
}

// bash-3.2$ echo "'$USER'"
// 'macbookm1pro'
// bash-3.2$ echo '$USER'
// $USER
// bash-3.2$ echo "d s "dd" d '' " ""
// d s dd d ''

void	remove_quote(char *line)
{
	char	quote_char;
	char	*start;
	char	*end;

	quote_char = '\0';
	while (*line)
	{
		if ((*line == '\'' || *line == '"') && quote_char == '\0')
		{
			start = line;
			end = line + 1;
			quote_char = *line;
			while (*end && *end != quote_char)
				end++;
			ft_memmove(start, start + 1, ft_strlen(start));
			ft_memmove(end - 1, end, ft_strlen(end) + 1);
			quote_char = '\0';
			line = end - 1;
		}
		else
			line++;
	}
}
