/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:16:12 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/17 19:30:14 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_heredoc(void)
{
	int		fd;

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
