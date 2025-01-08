/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:08:25 by mosmont           #+#    #+#             */
/*   Updated: 2024/10/16 20:43:10 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ts1;
	const unsigned char	*ts2;

	ts1 = (const unsigned char *)s1;
	ts2 = (const unsigned char *)s2;
	while (n--)
	{
		if (*ts1 != *ts2)
			return ((int)(*ts1 - *ts2));
		ts1++;
		ts2++;
	}
	return (0);
}
