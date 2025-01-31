/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_word_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:37:14 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/31 20:46:50 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_word_token(t_minishell *minishell, char **env)
{
	t_lexer	*current;

	current = minishell->input;
	while (current)
	{
		if (current->token_type == WORD)
		{
			current->value = expand_env_var(current->value, env, 0);
			remove_quote(current->value);
		}
		current = current->next;
	}
	if (g_error_code == 130)
		g_error_code = 0;
}
