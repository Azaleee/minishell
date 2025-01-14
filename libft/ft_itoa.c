/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:37:00 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/14 20:46:07 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(int n)
{
	int	result;

	result = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		result++;
	}
	while (n != 0)
	{
		n /= 10;
		result++;
	}
	return (result);
}

static void	int_to_string(int nb, char *str, int *i)
{
	if (nb >= 10)
		int_to_string(nb / 10, str, i);
	str[*i] = (nb % 10) + '0';
	(*i)++;
}

char	*ft_itoa(int n)
{
	char	*result;
	int		i;
	int		len;

	if (n == -2147483648)
		return ((char *)ft_strdup("-2147483648"));
	len = int_len(n);
	i = 0;
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	if (n < 0)
	{
		result[i++] = '-';
		n = -n;
	}
	int_to_string(n, result, &i);
	result[len] = '\0';
	return (result);
}
/*
int	main(void)
{
	printf("result : %s", ft_itoa(-0));
}*/
