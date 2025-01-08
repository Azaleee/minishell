/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:29:32 by mosmont           #+#    #+#             */
/*   Updated: 2024/11/22 16:21:11 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

size_t	ft_putstr(char *str)
{
	if (str == NULL)
		return (write(1, "(null)", 6));
	else
		return (write(1, str, ft_strlen(str)));
}

size_t	ft_putnbr(int nb)
{
	size_t	len;

	len = 0;
	if (nb == INT_MAX)
		len += ft_putstr("2147483647");
	else if (nb == INT_MIN)
		len += ft_putstr("-2147483648");
	else
	{
		if (nb < 0)
		{
			len += ft_putchar('-');
			nb = -nb;
		}
		if (nb / 10 != 0)
			len += ft_putnbr(nb / 10);
		len += ft_putchar('0' + nb % 10);
	}
	return (len);
}

size_t	ft_putadr(void *adr, const char *hexa_tab)
{
	char			remove_z;
	int				bytes;
	unsigned long	adress;
	char			hexa;
	size_t			i;

	if (adr == NULL)
		return (write(1, "0x0", 3));
	i = 0;
	bytes = 60;
	remove_z = 1;
	adress = (unsigned long)adr;
	write(1, "0x", 2);
	while (bytes >= 0)
	{
		hexa = hexa_tab[(adress >> bytes) & 0xf];
		if (hexa != '0' || bytes == 0 || remove_z == 0)
		{
			write(1, &hexa, 1);
			remove_z = 0;
			i++;
		}
		bytes -= 4;
	}
	return (i + 2);
}
