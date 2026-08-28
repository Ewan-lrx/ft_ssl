#ifndef INCLUDE_H
# define INCLUDE_H

# define rotl32(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
# define rotr32(x, n) (((x) >> (n)) | ((x) << (32 - (n))))

# include "ft_printf/ft_printf.h"
# include <stddef.h>
# include <unistd.h>
# include <stdint.h>

extern const uint32_t K[64];
extern const uint32_t K256[64];
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

typedef struct s_sha256_context {
    	uint32_t    h[8];
    	uint8_t     buffer[64];
    	size_t      buffer_len;
    	uint64_t    total_len;
}	t_sha256_context;

typedef enum e_input_type {
    	INPUT_FILE,
    	INPUT_STRING
}	t_input_type;

typedef struct s_input {
    	t_input_type    type;
    	char            *value;
}	t_input;

typedef struct s_flags {
	int	p_flag;
	int	r_flag;
	int	q_flag;
	int	s_flag;
	t_input	*inputs;
}	t_flags;

typedef struct s_command {
    	char    *name;
    	int     (*func)(int argc, char **argv);
} 	t_command;

int	cmd_md5(int argc, char **argv);
int	cmd_sha256(int argc, char **argv);

void    print_error(char *s);

//md5 algorithm functions
void	md5_init(void *context);
void	md5_update(void *context, uint8_t *data, size_t len);
void	md5_process_block(void *context, uint8_t *data);
void	md5_final(void *context, uint8_t *digest);

//sha256 algorith functions
void	sha256_init(void *context);
void	sha256_update(void *context, uint8_t *data, size_t len);
void	sha256_process_block(void *context, uint8_t data[64]);
void	sha256_final(void *context, uint8_t *digest);

//main
void	init_flags(t_flags *flags);
int	count_inputs(int argc, char **argv);
int	parse_args(int argc, char **argv, t_flags *flags);
int	check_args(int argc, char **argv, t_flags *flags);
int	dispatch(char *cmd_name, int argc, char **argv);
int	cmd_md5(int argc, char **argv);
int	cmd_sha256(int argc, char **argv);
int	process_command(t_hash_algo *algo, t_flags *flags, char *label);
int	hash_string(t_hash_algo *algo, t_flags *flags, char *label, char *str);
int	hash_file(t_hash_algo *algo, t_flags *flags, char *label, char *filename);
void	print_result(t_flags *flags, char *label, uint8_t *digest, size_t len, char *source, int is_file);

# endif
