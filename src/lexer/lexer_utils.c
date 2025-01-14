/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 21:35:08 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/14 20:46:36 by mosmont          ###   ########.fr       */
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
		value = ft_strdup("<<");
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		(*i)++;
		value = ft_strdup(">>");
	}
	else
		value = ft_substr(&input[*i], 0, 1);
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
