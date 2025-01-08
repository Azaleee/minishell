/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:21:08 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/08 20:32:16 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_input(t_minishell *minishell)
{
	t_lexer	*current;

	current = minishell->input;
	while (current->token_type != 9)
	{
		printf("Value -> %s\tToken -> %u\n", (char *)current->value, current->token_type);
		current = current->next;
	}
}

const char	*get_token_type_name(t_token_type type)
{
	const char	*token_type_names[7];

	token_type_names[0] = "WORD";
	token_type_names[1] = "PIPE";
	token_type_names[2] = "REDIRECT_IN";
	token_type_names[3] = "REDIRECT_OUT";
	token_type_names[4] = "REDIRECT_APPEND";
	token_type_names[5] = "REDIRECT_HEREDOC";
	if (type >= 0 && type < 6)
		return (token_type_names[type]);
	return ("UNKNOWN");
}

void	display_tokens(t_lexer *tokens)
{
	t_lexer	*token;

	token = tokens;
	while (token)
	{
		ft_printf("Token: \033[0;36m %s \033[0m |\t \
			Type: \033[0;35m %s \033[0m \n", token->value,
			get_token_type_name(token->token_type));
		ft_printf("--------------------------------------------------\n");
		token = token->next;
	}
}