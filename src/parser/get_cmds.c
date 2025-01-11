/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:10:22 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/11 01:05:37 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// t_cmds	*init_cmd(void)
// {
// 	t_cmds	*cmd;

// 	cmd = malloc(sizeof(t_cmds));
// 	cmd->args = NULL;
// 	cmd->input_file = NULL;
// 	cmd->output_file = NULL;
// 	cmd->next = NULL;
// 	return (cmd);
// }

// void	add_back_cmd(t_cmds **lst, t_cmds *new)
// {
// 	t_cmds	*current;

// 	if (!new)
// 		return ;
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	current = *lst;
// 	while (current->next != NULL)
// 	{
// 		if (!current)
// 			return ;
// 		current = current->next;
// 	}
// 	current->next = new;
// }

// void	add_arg(t_cmds *cmds, char *value)
// {
// 	char	**new_args;
// 	char	**args;
// 	char	**arg_ptr;

// 	args = cmds->args;
// 	arg_ptr = args;
// 	while (arg_ptr && *arg_ptr)
// 		arg_ptr++;
// 	new_args = malloc(sizeof(char *) * (arg_ptr - args + 2));
// 	arg_ptr = args;
// 	while (arg_ptr && *arg_ptr)
// 	{
// 		*new_args = ft_strndup(*arg_ptr, ft_strlen(*arg_ptr));
// 		arg_ptr++;
// 		new_args++;
// 	}
// 	*new_args = ft_strndup(value, ft_strlen(value));
// 	*(new_args + 1) = NULL;
// 	if (args)
// 		free_tab(args);
// 	cmds->args = new_args - (arg_ptr - args + 1);
// }

// t_cmds	*fill_cmds(t_lexer *tokens, t_cmds *cmds)
// {
// 	t_cmds	*current;

// 	current = init_cmd();
// 	while (tokens->token_type != T_EOF)
// 	{
// 		if (tokens->token_type == PIPE)
// 		{
// 			add_back_cmd(&cmds, current);
// 			current = init_cmd();
// 		}
// 		else if (tokens->token_type == WORD)
// 			add_arg(current, tokens->value);
// 		tokens = tokens->next;
// 	}
// 	return (cmds);
// }