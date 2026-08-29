/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-roux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:23:31 by ele-roux          #+#    #+#             */
/*   Updated: 2025/10/29 10:19:14 by ele-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*dest;

	dest = NULL;
	if (!s)
	{
		return (0);
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
		{
			dest = (char *) &s[i];
		}
		i++;
	}
	if ((unsigned char) c == '\0')
	{
		dest = (char *)&s[i];
	}
	return (dest);
}
