/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-roux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:15:30 by ele-roux          #+#    #+#             */
/*   Updated: 2025/11/17 10:37:46 by ele-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <limits.h>
# include <stdarg.h>
# include "libft/libft.h"

/*Main function*/

int		ft_printf(const char *str, ...);

/*useful Functions*/

int		hexa_len(unsigned long long n);
void	ft_puthexa(unsigned int nb, char *set);

/*Printing functions*/

int		ft_printf_pointer(unsigned long long ptr);
int		ft_print_hexa_lower(unsigned int n);
int		ft_print_hexa_upper(unsigned int nb);
int		printchar(char c);
int		printstr(char *str);
int		ft_putnbr(int n);
int		ft_print_unsigned(unsigned int n);

#endif
