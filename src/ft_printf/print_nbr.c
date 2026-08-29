/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-roux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:12:26 by ele-roux          #+#    #+#             */
/*   Updated: 2025/11/13 10:46:27 by ele-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	int_len(int n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n >= 10)
	{
		count++;
		n /= 10;
	}
	return (count);
}

int	ft_putnbr(int n)
{
	char	len;

	len = int_len(n);
	if (n == INT_MIN)
	{
		write (1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		n *= -1;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, 1);
	printchar((n % 10) + '0');
	return (len);
}
