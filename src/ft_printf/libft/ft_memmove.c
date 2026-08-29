/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-roux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:14:50 by ele-roux          #+#    #+#             */
/*   Updated: 2025/11/03 10:35:42 by ele-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*str_dest;
	char	*str_src;
	size_t	i;

	str_dest = (char *) dest;
	str_src = (char *) src;
	i = 0;
	if (str_dest > str_src)
	{
		while (n > 0)
		{
			str_dest[n - 1] = str_src[n - 1];
			n--;
		}
	}
	else
	{
		while (i < n)
		{
			str_dest[i] = str_src[i];
			i++;
		}
	}
	return (dest);
}
