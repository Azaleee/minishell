/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:56:22 by mosmont           #+#    #+#             */
/*   Updated: 2024/10/23 12:16:03 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_charset(char c, char const *charset)
{
	while (*charset)
	{
		if (*charset == c)
			return (1);
		charset++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char const	*start;
	char const	*end;
	char		*result;
	char		*temp;

	start = s1;
	end = s1 + ft_strlen(s1);
	while (*start && in_charset(*start, set))
		start++;
	while (end > start && in_charset(*(end - 1), set))
		end--;
	result = malloc((end - start + 1) * sizeof(char));
	if (!result)
		return (NULL);
	temp = result;
	while (start < end)
	{
		*temp = *start;
		temp++;
		start++;
	}
	*temp = '\0';
	return (result);
}

// int	main(void)
// {
// 	printf("%s", ft_strtrim("   dsalutr   ", "d r"));
// 	return (0);
// }