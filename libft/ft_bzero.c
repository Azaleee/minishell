/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:54:26 by mosmont           #+#    #+#             */
/*   Updated: 2024/10/24 15:33:00 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	bzero function is used to zero a memory area, 
	fill a memory block with bytes of value zero
*/

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
