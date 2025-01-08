/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:58:33 by mosmont           #+#    #+#             */
/*   Updated: 2024/10/17 20:13:24 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	strlcat function is used to concatenate a src str to a dest str, 
	while ensuring that the capacity of the dest str is not exceeded
*/

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	l_dest;
	size_t	l_src;
	char	*temp;
	size_t	s_remaining;

	l_dest = ft_strlen(dest);
	l_src = ft_strlen(src);
	temp = dest + l_dest;
	if (l_dest >= size)
		return (size + l_src);
	s_remaining = size - l_dest - 1;
	while (*src && s_remaining--)
		*temp++ = *src++;
	*temp = '\0';
	return (l_dest + l_src);
}
