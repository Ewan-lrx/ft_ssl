/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-roux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 10:52:38 by ele-roux          #+#    #+#             */
/*   Updated: 2025/10/23 14:42:43 by ele-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			count++;
		}
		i++;
	}
	return (count);
}

static	char	*fill(char const *s, char c)
{
	size_t	i;
	size_t	len;
	char	*dest;

	i = 0;
	len = 0;
	while (s[len] != c && s[len])
	{
		len++;
	}
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
	{
		return (0);
	}
	i = 0;
	while (i < len)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	size_t	index;
	size_t	words;
	size_t	i;

	i = 0;
	index = 0;
	words = count_words(s, c);
	dest = malloc(sizeof(char *) * (words + 1));
	if (!dest)
		return (0);
	while (index < words)
	{
		while (s[i] == c)
			i++;
		dest[index] = fill(&s[i], c);
		index++;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
		}
	}
	dest[index] = NULL;
	return (dest);
}
