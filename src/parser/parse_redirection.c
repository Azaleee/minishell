/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:17:53 by mosmont           #+#    #+#             */
/*   Updated: 2025/02/10 15:33:25 by mosmont          ###   ########.fr       */
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

void	get_heredoc_redir(t_minishell *minishell, t_cmds *cmds, t_lexer **token)
{
	char	*temp_file;

	if ((*token)->token_type == DLESS)
	{
		temp_file = create_temp_file(minishell->heredoc_counter);
		sigaction_handle();
		read_heredoc((char *)(*token)->next->value, temp_file);
		signal(SIGINT, handle_sigint);
		if (g_error_code == 130)
		{
			unlink(temp_file);
			cmds->error_file = -1;
		}
		else
			cmds->input_file = ft_strdup(temp_file);
		free(temp_file);
		(*minishell->heredoc_counter)++;
		*token = (*token)->next;
	}
}

void	get_input_redir(t_cmds *cmds, t_lexer **token)
{
	int	fd;

	fd = 0;
	if ((*token)->token_type == LESS)
	{
		fd = check_file_redir(cmds, (*token)->next->value, 0);
		if (fd != -1 && cmds->error_file != -1)
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
		close(fd);
	}
}

void	get_output_redir(t_cmds *cmds, t_lexer **token)
{
	int	fd;

	fd = 0;
	if ((*token)->token_type == GREAT)
	{
		fd = check_file_redir(cmds, (*token)->next->value, 1);
		if (fd != -1 && cmds->error_file != -1)
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
		close(fd);
	}
}

void	get_output_append_redir(t_cmds *cmds, t_lexer **token)
{
	int	fd;

	fd = 0;
	if ((*token)->token_type == DGREAT)
	{
		fd = check_file_redir(cmds, (*token)->next->value, 2);
		if (fd != -1 && cmds->error_file != -1)
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
		close(fd);
	}
}
