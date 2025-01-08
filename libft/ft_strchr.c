/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:57:26 by mosmont           #+#    #+#             */
/*   Updated: 2024/10/24 15:58:00 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	strchr function is used to search for the first
	occurence of a char in a string
*/

char	*ft_strchr(const char *str, int c)
{
	const char	*temp;

	temp = str;
	while (*temp)
	{
		if (*temp == (unsigned char)c)
			return ((char *)(temp));
		temp++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)temp);
	return (NULL);
}

// int	main(void)
// {
// 	int	j;

// 	j = 0;
// 	//printf("%p\n", ft_strchr("salut", 1025));
// 	while (j < 1025)
// 	{
// 		printf("%d - %p    / %d - %p\n", j, strchr("salut", j), j, 
//ft_strchr("salut", j));
// 		j++;
// 	}
// 	return (0);
// }
