/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:55:21 by mosmont           #+#    #+#             */
/*   Updated: 2024/10/24 15:38:35 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	memcpy function is used to copy a block of memory
	from a source to a destination
*/

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*c_dst;
	const unsigned char	*c_src;

	if (!dest && !src && n)
		return (NULL);
	c_dst = (unsigned char *)dest;
	c_src = (const unsigned char *)src;
	while (n)
	{
		*c_dst = *c_src;
		c_dst++;
		c_src++;
		n--;
	}
	return (dest);
}

// int	main(void)
// {
// 	char	dest[10] = "d";
// 	char	*src;

// 	src = "Saluasdasdasd";
// 	printf("%s", (char *)memcpy(((void *)0), ((void *)0), 0));
// 	return (0);
// }
