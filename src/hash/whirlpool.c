#include "hash_include.h"

void	whirlpool_init(void *context)
{
	t_whirlpool_context	*c;

	c = (t_whirlpool_context *)context;
	ft_bzero(c->hash, sizeof(c->hash));
	c->buffer_len = 0;
	c->total_len = 0;
}

static uint8_t	gf_mul(uint8_t a, uint8_t b)
{
	uint8_t	res;

	res = 0;
	while (b > 0)
	{
		if (b & 1)
			res ^= a;
		if (a & 0x80)
			a = (a << 1) ^ 0x1D;
		else
			a <<= 1;
		b >>= 1;
	}
	return (res);
}

static void	sub_bytes(uint8_t state[8][8])
{
	 size_t	i;
	 size_t	j;
	 
	 i = 0;
	 while(i < 8)
	 {
		 j = 0;
		 while (j < 8)
		 {
			 state[i][j] = WHIRLPOOL_SBOX[state[i][j]];
			 j++;
		 }
		 i++;
	 }
}

static void	shift_columns(uint8_t	state[8][8])
{
	uint8_t	tmp[8];
	size_t	i;
	size_t	j;

	j = 0;
	while(j < 8)
	{
		i = 0;
		while (i < 8)
		{
			tmp[i] = state[i][j];
			i++;
		}
		i = 0;
		while (i < 8)
		{
			state[(i + 8 - j) % 8][j] = tmp[i];
			i ++;
		}
		j++;
	}
}

static void	mix_rows(uint8_t state[8][8])
{
	uint8_t tmp[8][8];
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while(j < 8)
		{
			tmp[i][j] = 0;
			k = 0;
			while (k < 8)
			{
				tmp[i][j] ^= gf_mul(state[i][k], WHIRLPOOL_MDS[j][k]);
				k++;
			}
			j++;
		}
		i++;
	}
	ft_memcpy(state, tmp, 64);
}

static void	add_round_key(uint8_t state[8][8], uint8_t key[8][8])
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			state[i][j] ^= key[i][j];
			j++;
		}
		i++;
	}
}

void	whirlpool_process_block(t_whirlpool_context *c, uint8_t *block)
{
	uint8_t	state[8][8];
	uint8_t	key[8][8];
	size_t	r;
	size_t	i;
	size_t	j;

	r = 1;
	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			state[i][j] = block[i + 8 * j];
			key[i][j] = ((uint8_t *)c->hash)[i + 8 * j];
			j++;
		}
		i++;
	}
	add_round_key(state, key);
	while (r <= 10)
	{
		sub_bytes(key);
		shift_columns(key);
		mix_rows(key);
		add_round_key(key, (uint8_t (*)[8])WHIRLPOOL_RC[r]);
		sub_bytes(state);
		shift_columns(state);
		mix_rows(state);
		add_round_key(state, key);
		r++;
	}
	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			((uint8_t *)c->hash)[i + 8 * j] ^= block[i + 8 * j] ^ state[i][j];
			j++;
		}
		i++;
	}
}

void	whirlpool_update(void *context, uint8_t *data, size_t len)
{
	t_whirlpool_context	*c;
	size_t				i;
	
	c = (t_whirlpool_context *)context;
	i = 0;
	while (i < len)
	{
		c->buffer[c->buffer_len] = data[i];
		c->buffer_len++;
		c->total_len++;
		if (c->buffer_len == 64)
		{
			whirlpool_process_block(c, c->buffer);
			c->buffer_len = 0;
		}
		i++;
	}
}

void	whirlpool_final(void *context, uint8_t *digest)
{
	t_whirlpool_context	*c;
	uint64_t			bit_len;
	size_t				i;
	size_t				j;

	i = 0;
	c = (t_whirlpool_context *)context;
	c->buffer[c->buffer_len++] = 0x80;
	if (c->buffer_len > 32)
	{
		while(c->buffer_len < 64)
			c->buffer[c->buffer_len++] = 0x00;
		whirlpool_process_block(c, c->buffer);
		c->buffer_len = 0;
	}
	while (c->buffer_len < 32)
		c->buffer[c->buffer_len++] = 0x00;
	ft_bzero(&c->buffer[32], 32);
	bit_len = c->total_len * 8;
	while (i < 8)
	{
		c->buffer[63 - i] = (uint8_t)(bit_len >> (i * 8));
		i++;
	}
	whirlpool_process_block(c, c->buffer);
	ft_memcpy(digest, c->hash, 64);
	i = 0;
	while (i < 8)
	{
    		j = 0;
    		while (j < 8)
    		{
        		digest[i + 8 * j] = ((uint8_t *)c->hash)[i + 8 * j];
        		j++;
  		}
    		i++;
	}
}
