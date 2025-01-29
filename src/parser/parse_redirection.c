/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:17:53 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/29 15:41:08 by mosmont          ###   ########.fr       */
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

void	handle_heredoc_child(t_minishell *minishell, int pipe_fd[2], t_lexer **token, int *heredoc_counter)
{
	char    *temp_file;

	close(pipe_fd[0]);
	temp_file = create_temp_file(heredoc_counter);
	read_heredoc((char *)(*token)->next->value, temp_file);
	write(pipe_fd[1], temp_file, strlen(temp_file) + 1);
	free(temp_file);
	free_all(minishell);
	close(pipe_fd[1]);
	exit(0);
}

void	handle_heredoc_parent(int pipe_fd[2], t_cmds *cmds, t_lexer **token, pid_t pid)
{
	int     status;
	char    temp_file[256];

	close(pipe_fd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, SIG_DFL);
	if (read(pipe_fd[0], temp_file, sizeof(temp_file)) > 0)
		cmds->input_file = ft_strdup(temp_file);
	else
	{
		cmds->input_file = NULL;
		cmds->error_file = -1;
	}
	close(pipe_fd[0]);
	*token = (*token)->next;
}

void	get_heredoc_redir(t_minishell *minishell, t_cmds *cmds, t_lexer **token, int *heredoc_counter)
{
	int		pipe_fd[2];
	pid_t	pid;

	if ((*token)->token_type == DLESS)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		if (pid == 0)
			handle_heredoc_child(minishell, pipe_fd, token, heredoc_counter);
		else
			handle_heredoc_parent(pipe_fd, cmds, token, pid);
		(*heredoc_counter)++;
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
