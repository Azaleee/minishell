/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:34:57 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/09 13:18:52 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static int	ft_isspace(int c)
// {
// 	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
// 		|| c == '\r');
// }

// Si cest un espace ou un operateur et que cest pas entre quote
// && line[*i] != ' ' && !is_operator(line[*i]))
// 		|| ((is_operator(line[*i]) || line[*i] == ' ') && if_in_quote(line, i))

char	*parse_word(char *line, size_t *i)
{
	size_t	start;

	start = *i;
	while (line[*i] != '\0')
	{
		if ((line[*i] == ' ' || is_operator(line[*i])) && !if_in_quote(line, i))
			break ;
		(*i)++;
	}
	return (ft_substr(&line[start], 0, *i - start));
}

void	tokenization(t_minishell *minishell, char *line)
{
	size_t	i;
	char	*value;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (is_operator(line[i]) && if_in_quote(line, &i) == FALSE)
		{
			value = get_operator(line, &i);
			add_back_token(&minishell->input, new_token(value,
					determine_operator(value)));
		}
		else
		{
			value = parse_word(line, &i);
			add_back_token(&minishell->input, new_token(value, WORD));
		}
	}
	add_back_token(&minishell->input, new_token(NULL, T_EOF));
	// display_tokens(minishell->input);
}
