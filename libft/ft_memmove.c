/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:55:28 by mosmont           #+#    #+#             */
/*   Updated: 2024/10/24 15:52:24 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	memmove function is used to copy a block of memory from src to dest,
	and is designed to handle cases where memory areas overlap
*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*c_dst;
	const unsigned char	*c_src = (unsigned char *)src;

	if (!dest && !src && n)
		return (NULL);
	c_dst = (unsigned char *)dest;
	if (c_dst > c_src)
	{
		while (n--)
			c_dst[n] = c_src[n];
	}
	else
	{
		while (n--)
			*c_dst++ = *c_src++;
	}
	return (dest);
}

// int	main(void)
// {
// 	char	s[] = {65, 66, 67, 68, 69, 0, 45};

// 	printf("%s", (char *)ft_memmove(s+4, s + 2, 2));
// 	return (0);
// }