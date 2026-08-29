/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-roux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:09:25 by ele-roux          #+#    #+#             */
/*   Updated: 2025/11/17 10:37:14 by ele-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	hexa_len(unsigned long long n)
{
	int	count;

	count = 1;
	while (n >= 16)
	{
		n /= 16;
		count++;
	}
	return (count);
}

void	ft_puthexa(unsigned int nb, char *set)
{
	if (nb >= 16)
	{
		ft_puthexa((nb / 16), set);
	}
	ft_putchar_fd(set[nb % 16], 1);
}

int	ft_print_hexa_lower(unsigned int n)
{
	char	*set;
	int		len;

	len = hexa_len(n);
	set = "0123456789abcdef";
	ft_puthexa(n, set);
	return (len);
}

int	ft_print_hexa_upper(unsigned int nb)
{
	char	*set;
	int		len;

	len = hexa_len(nb);
	set = "0123456789ABCDEF";
	ft_puthexa(nb, set);
	return (len);
}
