/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:50:09 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/17 19:15:12 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_cmds	*init_cmd(void)
{
	t_cmds	*cmd;

	cmd = malloc(sizeof(t_cmds));
	cmd->args = NULL;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->is_append = FALSE;
	cmd->path_cmd = NULL;
	cmd->next = NULL;
	cmd->error_file = 0;
	return (cmd);
}

t_args	*init_arg(char *value)
{
	t_args	*new_arg;

	new_arg = malloc(sizeof(t_args));
	new_arg->arg = value;
	new_arg->next = NULL;
	return (new_arg);
}

t_lexer	*new_token(char *content, t_tok_t token)
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
