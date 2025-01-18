/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:36:35 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/18 22:57:04 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_file(char *file, int mode, int append_mode)
{
	int	fd;

	if (mode == 0)
		fd = open(file, O_RDONLY);
	else if (mode == 1)
	{
		if (append_mode == 0)
			fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
		return (-1);
	return (fd);
}

void	set_input_redir(t_cmds *current, t_minishell *minishell, int i)
{
	int	fd_in;

	fd_in = 0;
	if (current->input_file)
	{
		fd_in = open_file(current->input_file, 0, current->is_append);
		if (fd_in == -1)
		{
			perror(current->input_file);
			exit(1);
		}
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		if (ft_strncmp(current->input_file, "/tmp/heredoc", 12) == 0)
		{
			if (unlink(current->input_file) == -1)
				perror("set_input_redir: unlink");
		}
	}
	else if (i > 0)
		dup2(minishell->pipes[i - 1][0], STDIN_FILENO);
}

void	set_output_redir(t_cmds *current, t_minishell *minishell, int i)
{
	int	fd_out;

	fd_out = 1;
	if (current->output_file)
	{
		fd_out = open_file(current->output_file, 1, current->is_append);
		if (fd_out == -1)
		{
			perror(current->output_file);
			exit(1);
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else if (i < minishell->nb_cmd - 1)
		dup2(minishell->pipes[i][1], STDOUT_FILENO);
}
