#ifndef INCLUDE_H
# define INCLUDE_H

# define rotl32(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

# include "ft_printf/ft_printf.h"
# include <stddef.h>
# include <unistd.h>
# include <stdint.h>

extern const uint32_t K[64];
extern const uint32_t S[64];

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
	size_t		current_round;
}	t_md5_context;

typedef struct s_data_block {
        uint32_t        a, b, c, d, e, f, g, h;
}       t_data_block;

typedef struct s_sha_context {
        uint32_t        a, b, c, d, e, f, g, h;
        uint8_t         buffer[64];
        size_t          buffer_len;
        uint64_t        total_len;
        size_t          current_round;
}       t_sha_context;


typedef struct s_flags {
	int	p_flag;
	int	r_flag;
	int	q_flag;
	int	s_flag;
}	t_flags;

void    print_error(char *s);

//md5 algorithm functions
void md5_init(void *context);
void md5_update(void *context, uint8_t *data, size_t len);
void md5_process_block(void *context, uint8_t *data);
void md5_final(void *context, uint8_t *digest);

# endif
