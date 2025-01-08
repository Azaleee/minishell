/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:58:50 by mosmont           #+#    #+#             */
/*   Updated: 2024/10/23 18:44:48 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	strlen function is used to calculate the lenght of a string
*/

size_t	ft_strlen(const char *str)
{
	const char	*temp;

	temp = str;
	while (*temp)
		temp++;
	return ((size_t)(temp - str));
}
