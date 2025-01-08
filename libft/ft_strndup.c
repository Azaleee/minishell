/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:57:56 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/07 22:12:13 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	strdup function is used to create a copy of a string. 
	It dynamically allocates memory for this copy and returns a pointer 
	to this memory
*/

char	*ft_strndup(const char *s, size_t len)
{
	int		i;
	char	*final;

	final = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!final)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && len)
	{
		final[i] = s[i];
		len--;
		i++;
	}
	final[i] = '\0';
	return ((char *)final);
}
