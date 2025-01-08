/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:58:59 by mosmont           #+#    #+#             */
/*   Updated: 2024/10/15 17:58:59 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*result;
	char	*temp;

	if (!s || !f)
		return (NULL);
	i = 0;
	result = malloc(ft_strlen(s) + 1);
	if (!result)
		return (NULL);
	temp = result;
	while (*s)
	{
		*temp = (*f)(i, *s);
		i++;
		s++;
		temp++;
	}
	*temp = '\0';
	return (result);
}
