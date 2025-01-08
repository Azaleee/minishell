/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:55:34 by mosmont           #+#    #+#             */
/*   Updated: 2024/10/24 15:33:03 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	memset function is used to fill a memory area with a specific value.
*/

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n--)
		*p++ = (unsigned char)c;
	return ((void *)s);
}

// int	main(void)
// {
// 	char str[50] = "Hello World!";
// 	ft_memset(str, 0, 5);
// 	printf("%s\n", str);
// 	return (0);
// }
