#ifndef INCLUDE_H
# define INCLUDE_H

# include "ft_printf/ft_printf.h"
# include <stddef.h>
# include <unistd.h>


typedef struct s_hash_algo {
	void	(*init)(void *context);
	void	(*update)(void *context, uint8_t *data, size_t len);
	void	(*final)(void *context, uint8_t *digest);
	size_t	digest_size;
}	t_hash_algo;

void    print_error(char *s);

# endif
