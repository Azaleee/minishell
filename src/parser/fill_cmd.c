/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:10:22 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/17 19:14:10 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_redirection(t_cmds *cmds, t_lexer **token)
{
	get_heredoc_redir(cmds, token);
	get_input_redir(cmds, token);
	get_output_redir(cmds, token);
	get_output_append_redir(cmds, token);
}

void	fill_struct_cmds(t_cmds **cmds, t_lexer *token)
{
	t_cmds	*current_cmd;

	current_cmd = init_cmd();
	while (token)
	{
		if (token->token_type == PIPE)
		{
			lst_add_back((void **)cmds, current_cmd,
				get_next_cmd, set_next_cmd);
			current_cmd = init_cmd();
		}
		else if (token->token_type == LESS || token->token_type == GREAT
			|| token->token_type == DGREAT || token->token_type == DLESS)
			set_redirection(current_cmd, &token);
		else if (token->token_type == WORD)
			lst_add_back((void **)&current_cmd->args, init_arg(token->value),
				get_next_args, set_next_args);
		token = token->next;
	}
	if (current_cmd)
		lst_add_back((void **)cmds, current_cmd,
			get_next_cmd, set_next_cmd);
}
