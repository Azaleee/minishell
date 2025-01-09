/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 21:35:08 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/09 13:18:21 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	*get_operator(char *input, size_t *i)
{
	char	*value;

	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		(*i)++;
		value = ft_strndup("<<", 2);
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		(*i)++;
		value = ft_strndup(">>", 2);
	}
	else
		value = ft_strndup(&input[*i], 1);
	(*i)++;
	return (value);
}

t_token_type	determine_operator(char *value)
{
	if (value[0] == '|')
		return (PIPE);
	else if (value[0] == '<' && value[1] == '<')
		return (DLESS);
	else if (value[0] == '>' && value[1] == '>')
		return (DGREAT);
	else if (value[0] == '<')
		return (LESS);
	else if (value[0] == '>')
		return (GREAT);
	else
		return (-1);
}

// "in quote | "

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
