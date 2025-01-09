/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepend_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:51:28 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/09 16:57:18 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_prepend_char(const char *str, char c)
{
	size_t	len;
	char	*new_str;

	len = strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	new_str[0] = c;
	strcpy(new_str + 1, str);
	return (new_str);
}