/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:51:38 by mosmont           #+#    #+#             */
/*   Updated: 2024/10/16 20:55:33 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	strnstr is a function that searches for the first 
	occurence of a substring in a main string, but with a size limit
*/

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*h_temp;
	const char	*n_temp;
	size_t		remaining_len;

	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack && len)
	{
		h_temp = haystack;
		n_temp = needle;
		remaining_len = len;
		while (*h_temp == *n_temp && *n_temp && remaining_len > 0)
		{
			h_temp++;
			n_temp++;
			remaining_len--;
		}
		if (*n_temp == '\0')
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
