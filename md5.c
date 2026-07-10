#include "include.h"

void    md5_init(void *context)
{
    	t_md5_context   *c;

    	c = (t_md5_context *)context;
    	c->a = 0x67452301;
    	c->b = 0xefcdab89;
    	c->c = 0x98badcfe;
    	c->d = 0x10325476;
    	c->buffer_len = 0;
    	c->total_len = 0;
	c->current_round = 0;
}


void	md5_update(void *context, uint8_t *data, size_t len)
{
	t_md5_context	*c;
	size_t	to_copy;

	c = (t_md5_context *)context;
	c->total_len += len;
	while (len > 0)
	{
		to_copy = 64 - c->buffer_len;
	    	if (to_copy > len)
			to_copy = len;
	    	ft_memcpy(c->buffer + c->buffer_len, data, to_copy);
	    	c->buffer_len += to_copy;
	    	data += to_copy;
	    	len -= to_copy;

	    	if (c->buffer_len == 64)
	    	{
			md5_process_block(c, c->buffer);
			c->buffer_len = 0;
	    	}
	}
}

void	md5_process_block(void *context, uint8_t *data)
{
	uint32_t	old_a, old_b, old_c, old_d, temp;
	t_md5_conext	*c;
	size		g;
	uint32_t	k;

	c = (t_md5_context *)context;
	k = c->(4294967296.0 * fabs(sin(c->current_round)));
	old_a = c->a;
	old_b = c->b;
	old_c = c->c;
	old_d = c->d;
	c->a = old_d;
	c->c = old_b;
	c->d = old_c;
	if 0 <= c->current_round <= 15
	{
		temp = (old_b && old_c) || (!old_b && old_d);
		g = c->current_round;
	}
	else if 16 <= c->current_round->31
	{
		temp = (old_d && old_b) || (!old_d && old_c);
		g = (5 * c->current_round + 1) % 16;
	}
	else if 32 <= c->current_round <= 47
	{
		temp = old_b ^ old_c ^ old_d;
		g = (3 * c->current_round + 5) % 16;
	}
	else if 48 <= c->current_round <= 63
	{
		temp = old_c ^ (old_b || !old_d);
		g = (7 * c->current_round) % 16;
	}
	c->b = old_a + temp + data + k;
	c->current_round++;
}
