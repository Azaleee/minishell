/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:24:58 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/09 20:22:30 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*new_token(char *content, t_token_type token)
{
	t_lexer	*lstnew;

	lstnew = malloc(sizeof(t_lexer));
	if (!lstnew)
		return (NULL);
	if (content)
		lstnew->value = content;
	else
		lstnew->value = NULL;
	lstnew->token_type = token;
	lstnew->next = NULL;
	return (lstnew);
}

void	add_back_token(t_lexer **lst, t_lexer *new)
{
	t_lexer	*current;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
	{
		if (!current)
			return ;
		current = current->next;
	}
	current->next = new;
}

void	token_clear(t_minishell *minishell)
{
	t_lexer	*temp;
	t_lexer	*current;

	current = minishell->input;
	while (current)
	{
		temp = current->next;
		free(current->value);
		free(current);
		current = temp;
	}
	minishell->input = NULL;
}
