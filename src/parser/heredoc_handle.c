/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:16:12 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/29 15:39:04 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_heredoc(char *input_file)
{
	int		fd;

	fd = open(input_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return (fd);
}

char	*create_temp_file(int *heredoc_counter)
{
	char	*file;
	char	*counter;

	counter = ft_itoa(*heredoc_counter);
	file = ft_strjoin("/tmp/heredoc", counter);
	free(counter);
	return (file);
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	exit(130);
}

void	read_heredoc(char *eof, char *input_file)
{
	char	*line;
	int		fd;
	
	signal(SIGINT, handle_sigint_heredoc);
    signal(SIGQUIT, SIG_IGN);
	line = NULL;
	fd = open_heredoc(input_file);
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
	close(fd);
}
