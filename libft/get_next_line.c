/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:57:09 by mosmont           #+#    #+#             */
/*   Updated: 2024/12/29 04:51:25 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_line(int fd, char *buffer, char *line)
{
	int	bytes_read;

	bytes_read = 1;
	if (check_eof(buffer) == 1)
	{
		cut_buffer(buffer);
		line = ft_strjoin_gnl(line, buffer);
	}
	while (bytes_read > 0 && check_eof(buffer) == 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			return (free(line), NULL);
		}
		buffer[bytes_read] = '\0';
		line = ft_strjoin_gnl(line, buffer);
		if (line == NULL)
			return (NULL);
	}
	return (line);
}

void	cut_buffer(char *buffer)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	while (buffer[i])
		buffer[j++] = buffer[i++];
	buffer[j] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
	{
		buffer[0] = '\0';
		return (NULL);
	}
	line = malloc(1);
	if (line == NULL)
		return (NULL);
	line[0] = '\0';
	line = read_line(fd, buffer, line);
	if (line == NULL)
		free(line);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	fd = open("giant_line.txt", O_RDONLY);
// 	i = 1;
// 	while ((line) != NULL)
// 	{
// 		line = get_next_line(fd);
// 		printf("%d: %s", i, line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// }
