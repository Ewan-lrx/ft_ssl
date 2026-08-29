/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-roux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:11:24 by ele-roux          #+#    #+#             */
/*   Updated: 2025/11/12 15:12:16 by ele-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	printstr(char *str)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	if (!str)
	{
		printstr("(null)");
		return (6);
	}
	while (str[i])
	{
		printchar(str[i]);
		len++;
		i++;
	}
	return (len);
}
