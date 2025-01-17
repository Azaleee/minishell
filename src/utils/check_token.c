/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:27:16 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/16 16:33:14 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	printf_error_token(char *value)
{
	ft_putstr_fd("syntax error near unexpected token '", 2);
	ft_putstr_fd(value, 2);
	ft_putstr_fd("'\n", 2);
	// ERROR CODE
}

int	syntax_token_good(t_lexer *token)
{
	while (token)
	{
		if ((token->token_type >= 1 && token->token_type <= 4)
			&& token->next == NULL)
				return (printf_error_token("newline"), FALSE);
		if ((token->token_type == PIPE && token->next->token_type == PIPE))
			return (printf_error_token(token->next->value), FALSE);
		if ((token->token_type >= 1 && token->token_type <= 4)
			&& token->next->token_type != WORD)
				return (printf_error_token(token->next->value), FALSE);
		token = token->next;
	}
	return (TRUE);
}