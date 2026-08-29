/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-roux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:23:19 by ele-roux          #+#    #+#             */
/*   Updated: 2025/10/28 12:05:28 by ele-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	int_len(long n)
{
	size_t	count;

	count = 1;
	if (n < 0)
	{
		n *= -1;
	}
	while (n >= 10)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static	char	*assignation(char *dest, size_t	len_dest, int n)
{
	size_t	i;

	i = 1;
	while (len_dest >= i)
	{
		dest[len_dest - i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	dest[len_dest] = '\0';
	return (dest);
}

char	*ft_itoa(int n)
{
	char	*dest;
	size_t	is_ng;
	size_t	len_dest;

	len_dest = int_len((long)n);
	is_ng = 0;
	if (n < 0)
		is_ng = 1;
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	dest = malloc(sizeof(char) * (len_dest + is_ng + 1));
	if (!dest)
		return (0);
	if (n < 0)
	{
		n *= -1;
		dest = assignation(dest, len_dest + is_ng, n);
		dest[0] = '-';
	}
	else
		dest = assignation(dest, len_dest, n);
	return (dest);
}
