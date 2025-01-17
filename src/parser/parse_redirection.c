/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:17:53 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/17 19:22:41 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_file_redir(t_cmds *cmds, char *file, int mode)
{
	int	fd;

	if (mode == 0 && cmds->error_file != -1)
		fd = open(file, O_RDONLY);
	else if (mode == 1 && cmds->error_file != -1)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (mode == 2 && cmds->error_file != -1)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
		return (-1);
	if (fd == -1)
		perror(file);
	return (fd);
}

void	get_heredoc_redir(t_cmds *cmds, t_lexer **token)
{
	if ((*token)->token_type == DLESS)
	{
		free(cmds->input_file);
		cmds->input_file = ft_strdup("/tmp/heredoc.tmp");
		read_heredoc((char *)(*token)->next->value);
		(*token) = (*token)->next;
	}
}

void	get_input_redir(t_cmds *cmds, t_lexer **token)
{
	if ((*token)->token_type == LESS)
	{
		if (check_file_redir(cmds, (*token)->next->value, 0) != -1
			&& cmds->error_file != -1)
		{
			free(cmds->input_file);
			cmds->input_file = ft_strdup((*token)->next->value);
			(*token) = (*token)->next;
		}
		else
		{
			free(cmds->input_file);
			cmds->input_file = ft_strdup("\0");
			cmds->error_file = -1;
			(*token) = (*token)->next;
		}
	}
}

void	get_output_redir(t_cmds *cmds, t_lexer **token)
{
	if ((*token)->token_type == GREAT)
	{
		if (check_file_redir(cmds, (*token)->next->value, 1) != -1
			&& cmds->error_file != -1)
		{
			if (cmds->output_file)
				free(cmds->output_file);
			cmds->output_file = ft_strdup((*token)->next->value);
			(*token) = (*token)->next;
		}
		else
		{
			if (cmds->output_file)
				free(cmds->output_file);
			cmds->output_file = ft_strdup("\0");
			cmds->error_file = -1;
			(*token) = (*token)->next;
		}
	}
}

void	get_output_append_redir(t_cmds *cmds, t_lexer **token)
{
	if ((*token)->token_type == DGREAT)
	{
		if (check_file_redir(cmds, (*token)->next->value, 2) != -1
			&& cmds->error_file != -1)
		{
			if (cmds->output_file)
				free(cmds->output_file);
			cmds->output_file = ft_strdup((*token)->next->value);
			cmds->is_append = TRUE;
			(*token) = (*token)->next;
		}
		else
		{
			if (cmds->output_file)
				free(cmds->output_file);
			cmds->output_file = ft_strdup("\0");
			cmds->error_file = -1;
			(*token) = (*token)->next;
		}
	}
}
