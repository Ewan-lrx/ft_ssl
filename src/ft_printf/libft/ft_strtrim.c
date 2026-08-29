/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-roux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:02:57 by ele-roux          #+#    #+#             */
/*   Updated: 2025/10/23 14:42:28 by ele-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_start(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;

	i = 0;
	start = 0;
	while (set[i] && s1[start])
	{
		if (s1[start] == set[i])
		{
			start++;
			i = 0;
		}
		else
		{
			i++;
		}
	}
	return (start);
}

static int	ft_find_end(char const *s1, char const *set)
{
	size_t	i;
	size_t	end;

	end = ft_strlen(s1) - 1;
	i = 0;
	while (set[i] && i <= end)
	{
		if (s1[end] == set[i])
		{
			end--;
			i = 0;
		}
		else
		{
			i++;
		}
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*dest;

	start = ft_find_start(s1, set);
	end = ft_find_end(s1, set);
	dest = ft_substr(s1, start, end - start + 1);
	return (dest);
}
