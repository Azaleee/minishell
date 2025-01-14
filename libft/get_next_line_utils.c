/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:08:56 by mosmont           #+#    #+#             */
/*   Updated: 2024/12/29 01:30:38 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_eof(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

size_t	eof_index(char *string)
{
	size_t	i;

	if (string == NULL)
		return (0);
	i = 0;
	while (string[i] != '\0' && string[i] != '\n')
		i++;
	if (string[i] == '\n')
		i++;
	return (i);
}

size_t	ft_strlen_gnl(char *string)
{
	size_t	i;

	if (string == NULL)
		return (0);
	i = 0;
	while (string[i])
		i++;
	return (i);
}

char	*free_and_reset(char *string1, char *final_string)
{
	if (string1)
	{
		free(string1);
		string1 = NULL;
	}
	if (final_string)
	{
		if (final_string[0] == '\0')
		{
			free(final_string);
			final_string = NULL;
		}
	}
	return (final_string);
}

char	*ft_strjoin_gnl(char *string1, char *string2)
{
	char	*final_string;
	size_t	i;
	size_t	j;

	final_string = malloc((eof_index(string1) + eof_index(string2) + 1) * 1);
	if (final_string != NULL)
	{
		i = 0;
		while (string1 && string1[i])
		{
			final_string[i] = string1[i];
			i++;
		}
		j = 0;
		while (string2 && string2[j] && string2[j] != '\n')
		{
			final_string[i + j] = string2[j];
			j++;
		}
		if (string2[j] == '\n')
			final_string[i + j++] = '\n';
		final_string[i + j] = '\0';
	}
	return (free_and_reset(string1, final_string));
}
