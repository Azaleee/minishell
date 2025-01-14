/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:00:54 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/14 20:46:18 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len < start + len)
		len = s_len - start;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	sub[len] = '\0';
	return ((char *)sub);
	// char	*new_str;
	// size_t	i;

	// if (!s)
	// 	return (NULL);
	// i = 0;
	// new_str = &s[start];
	// if (ft_strlen(s) < start + len)
	// 	len = ft_strlen(s) - start;
	// if (len > 0)
	// {
	// 	i = 0;
	// 	while (new_str[i] && i < len)
	// 		i++;
	// 	if (i == len)
	// 		new_str[i] = '\0';
	// }
	// return (new_str);
}

/*int	main(void)
{
	char	*s;

	s = ft_substr("tripouille", 100, 1);
	printf("-%s-\n", s);
}*/

/*
	*s = "salut je suis"
			3      10
			start  len

	*s = "salut je suis"
			3         13 16
			start  			len
*/

/*
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) < start + len)
		len = ft_strlen(s) - start;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, len);
	sub[len] = '\0';
	return ((char *)sub);
}*/
