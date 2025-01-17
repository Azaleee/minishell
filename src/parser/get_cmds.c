/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:10:22 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/16 21:01:07 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*get_next_cmd(void *node)
{
	return (((t_cmds *)node)->next);
}

void	set_next_cmd(void *node, void *next)
{
	((t_cmds *)node)->next = next;
}

void	*get_next_args(void *node)
{
	return (((t_args *)node)->next);
}

void	set_next_args(void *node, void *next)
{
	((t_args *)node)->next = (t_args *)next;
}

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

// /tmp/heredoc.tmp

int	open_heredoc()
{
	int		fd;
	int		status;
	pid_t	pid;

	fd = open("/tmp/heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return (fd);
}

void	read_heredoc(char *eof)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open_heredoc();
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			break ;
		}
		if (ft_strncmp(line, eof, ft_strlen(eof)) == 0
			&& line[ft_strlen(eof)] == '\n')
			break ;
		if (line != NULL)
			write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
}

// void	handle_heredoc(t_cmds *cmds, t_lexer **token)
// {
// 	t_lexer	*init_pos;
// 	t_lexer *current;

// 	init_pos = *token;
// 	current = *token;
// 	while (current && current->token_type != PIPE)
// 	{
// 		if (current->token_type == DLESS)
// 		{
// 			free(cmds->input_file);
// 			cmds->input_file = ft_strdup("/tmp/heredoc.tmp");
// 			printf("EOF -> %s\n", (char *)current->next->value);
// 			read_heredoc((char *)current->next->value);
// 			current = current->next->next;
// 		}
// 		else
// 			current = current->next;
// 	}
// 	*token = current;
// 	printf("AFTER HERE_DOC -> %s\n", (char *)(*token)->value);
// }

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

void	set_redirection(t_cmds *cmds, t_lexer **token)
{
	if ((*token)->token_type == DLESS)
	{
		size_t i;
		i = ft_strlen((char *)(*token)->next->value) / 2;
		char quoted_eof = if_in_quote((char *)(*token)->next->value, &i);
		printf("size d 2 -> %zu CHECK EOF %c\n", i, quoted_eof);
		free(cmds->input_file);
		cmds->input_file = ft_strdup("/tmp/heredoc.tmp");
		printf("EOF -> %s\n", (char *)(*token)->next->value);
		read_heredoc((char *)(*token)->next->value);
		(*token) = (*token)->next;
	}
	if ((*token)->token_type == LESS)
	{
		if (check_file_redir(cmds, (*token)->next->value, 0) != -1 && cmds->error_file != -1)
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
	if ((*token)->token_type == GREAT)
	{
		if (check_file_redir(cmds, (*token)->next->value, 1) != -1 && cmds->error_file != -1)
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
	if ((*token)->token_type == DGREAT)
	{
		if (check_file_redir(cmds, (*token)->next->value, 2) != -1 && cmds->error_file != -1)
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

void	fill_struct_cmds(t_cmds **cmds, t_lexer *token)
{
	t_cmds	*current_cmd;

	current_cmd = init_cmd();
	while (token)
	{
		// handle_heredoc(current_cmd, &token);
		if (token->token_type == PIPE)
		{
			lst_add_back((void **)cmds, current_cmd,
				get_next_cmd, set_next_cmd);
			current_cmd = init_cmd();
		}
		else if (token->token_type == LESS || token->token_type == GREAT || token->token_type == DGREAT || token->token_type == DLESS)
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
