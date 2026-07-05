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

typedef struct s_md5_context {
	uint32_t	a, b, c, d;
	uint8_t		buffer[64];
	size_t		buffer_len;
	uint64_t	total_len;
}	t_md5_context;

void    print_error(char *s);

# endif
