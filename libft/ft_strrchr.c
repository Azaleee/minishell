/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:59:32 by mosmont           #+#    #+#             */
/*   Updated: 2024/10/23 17:50:06 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	strrchr function is used to search for 
	the last occurrence of a given char in a string
*/

char	*ft_strrchr(const char *str, int c)
{
	const char	*s_temp;
	const char	*p_temp;

	s_temp = str;
	p_temp = NULL;
	while (*s_temp)
	{
		if (*s_temp == (unsigned char)c)
			p_temp = s_temp;
		s_temp++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)str + ft_strlen(str));
	if (!p_temp)
		return (NULL);
	return ((char *)p_temp);
}
/*
int	main(void)
{
	printf("%s", strrchr("testeff", 'd'));
	return (0);
}*/
