/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-roux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:51:37 by ele-roux          #+#    #+#             */
/*   Updated: 2025/10/31 15:16:02 by ele-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;

	if (size != 0 && nmemb > ((size_t) - 1 / size))
	{
		return (NULL);
	}
	dest = malloc(size * nmemb);
	if (!dest)
	{
		return (NULL);
	}
	ft_memset(dest, '\0', nmemb * size);
	return (dest);
}
