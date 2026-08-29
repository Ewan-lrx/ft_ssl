/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-roux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:10:27 by ele-roux          #+#    #+#             */
/*   Updated: 2025/11/13 10:39:28 by ele-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putptr(unsigned long long nb, char *set)
{
	if (nb >= 16)
	{
		ft_putptr((nb / 16), set);
	}
	ft_putchar_fd(set[nb % 16], 1);
}

int	ft_print_ptr(unsigned long long nb)
{
	char	*set;
	int		i;

	i = hexa_len(nb);
	set = "0123456789abcdef";
	ft_putptr(nb, set);
	return (i);
}

int	ft_printf_pointer(unsigned long long ptr)
{
	int	len;

	if (!ptr)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	len = hexa_len(ptr) + 2;
	ft_putstr_fd("0x", 1);
	if (ptr == 0)
		ft_putchar_fd('0', 1);
	else
		ft_print_ptr(ptr);
	return (len);
}
