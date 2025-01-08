/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:17:05 by mosmont           #+#    #+#             */
/*   Updated: 2024/11/22 16:21:35 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdarg.h>

size_t	ft_putunbr(unsigned int nb)
{
	if (nb / 10)
		return (ft_putunbr(nb / 10) + ft_putunbr(nb % 10));
	else
		return (ft_putchar(nb + '0'));
}

size_t	ft_puthexa(unsigned int nb, char *hexa)
{
	size_t			len;

	len = 0;
	if (nb > 16 - 1)
		len += ft_puthexa(nb / 16, hexa);
	len += ft_putchar(hexa[nb % 16]);
	return (len);
}

size_t	check(va_list *args, char hook)
{
	if (hook == 'd' || hook == 'i')
		return (ft_putnbr(va_arg(*args, int)));
	if (hook == 'c')
		return (ft_putchar(va_arg(*args, int)));
	if (hook == 's')
		return (ft_putstr(va_arg(*args, char *)));
	if (hook == 'p')
		return (ft_putadr(va_arg(*args, void *), "0123456789abcdef"));
	if (hook == 'u')
		return (ft_putunbr(va_arg(*args, unsigned int)));
	if (hook == 'x')
		return (ft_puthexa(va_arg(*args, unsigned int), "0123456789abcdef"));
	if (hook == 'X')
		return (ft_puthexa(va_arg(*args, unsigned int), "0123456789ABCDEF"));
	if (hook == '%')
		return (write(1, "%", 1));
	else
		return (-1);
}

int	ft_printf(const char *hook, ...)
{
	int		i;
	va_list	args;
	int		final;

	va_start(args, hook);
	i = 0;
	final = 0;
	while (hook[i] != '\0')
	{
		if (hook[i] == '%')
		{
			i++;
			final += check(&args, hook[i]);
		}
		else
			final += ft_putchar(hook[i]);
		i++;
	}
	va_end(args);
	return (final);
}
