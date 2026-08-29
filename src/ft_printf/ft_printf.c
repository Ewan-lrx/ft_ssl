/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-roux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:00:57 by ele-roux          #+#    #+#             */
/*   Updated: 2025/11/13 10:50:44 by ele-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_flags(va_list args, const char c)
{
	size_t	len;

	len = 0;
	if (c == 'c')
		len += printchar(va_arg(args, int));
	else if (c == 's')
		len += printstr(va_arg(args, char *));
	else if (c == 'x')
		len += ft_print_hexa_lower(va_arg(args, unsigned int));
	else if (c == 'X')
		len += ft_print_hexa_upper(va_arg(args, unsigned int));
	else if (c == '%')
		len += printchar('%');
	else if (c == 'p')
		len += ft_printf_pointer(va_arg(args, unsigned long long));
	else if (c == 'i' || c == 'd')
		len += ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		len += ft_print_unsigned(va_arg(args, unsigned int));
	return (len);
}

int	ft_printf(const char *str, ...)
{
	size_t	i;
	va_list	args;
	int		len;

	len = 0;
	i = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			len += check_flags(args, str[i + 1]);
			i += 2;
		}
		else
		{
			len += printchar(str[i]);
			i++;
		}
	}
	va_end(args);
	return (len);
}
