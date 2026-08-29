/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-roux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:11:49 by ele-roux          #+#    #+#             */
/*   Updated: 2025/11/13 10:45:20 by ele-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	unsigned_len(unsigned int n)
{
	int	count;

	count = 1;
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_uitoa(unsigned int n)
{
	char	*dest;
	int		len;

	len = unsigned_len(n);
	dest = ft_calloc(len + 1, sizeof(char));
	if (!dest)
		return (NULL);
	ft_memset(dest, '0', len);
	while (n != 0)
	{
		dest[len - 1] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (dest);
}

int	ft_print_unsigned(unsigned int n)
{
	int		len;
	char	*dest;

	len = unsigned_len(n);
	dest = ft_uitoa(n);
	if (!dest)
		return (0);
	printstr(dest);
	free (dest);
	return (len);
}
