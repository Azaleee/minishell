/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:51:30 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/17 19:22:33 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	args_clear(t_args **args)
{
	t_args	*temp;
	t_args	*current;

	current = *args;
	while (current)
	{
		temp = current->next;
		if (current)
			free(current);
		current = temp;
	}
	args = NULL;
}

void	cmds_clear(t_minishell *minishell)
{
	t_cmds	*temp;
	t_cmds	*current;

	if (minishell->cmds == NULL)
		return ;
	current = minishell->cmds;
	while (current)
	{
		temp = current->next;
		if (current->path_cmd)
			free(current->path_cmd);
		if (current->args)
			args_clear(&current->args);
		if (current->input_file)
			free(current->input_file);
		if (current->output_file)
			free(current->output_file);
		if (current)
			free(current);
		current = temp;
	}
	minishell->cmds = NULL;
}

void	token_clear(t_minishell *minishell)
{
	t_lexer	*temp;
	t_lexer	*current;

	current = minishell->input;
	while (current)
	{
		temp = current->next;
		if (current->value)
		{
			free(current->value);
			current->value = NULL;
		}
		if (current)
			free(current);
		current = temp;
	}
	minishell->input = NULL;
}
