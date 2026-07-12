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

void md5_process_block(void *context, uint8_t *data)
{
	t_md5_context *c;
	uint32_t a, b, cc, d;
	uint32_t m[16];
	uint32_t f, temp;
    	int i, g;
    
	c = (t_md5_context *)context;
    	for (i = 0; i < 16; i++)
		m[i] = (uint32_t)data[i * 4]
	   		| ((uint32_t)data[i * 4 + 1] << 8)
	   		| ((uint32_t)data[i * 4 + 2] << 16)
	   		| ((uint32_t)data[i * 4 + 3] << 24);
    	a = c->a;
    	b = c->b;
    	cc = c->c;
    	d = c->d;
    	for (i = 0; i < 64; i++)
    	{
		if (i < 16)
		{
	    		f = (b & cc) | (~b & d);
	    		g = i;
		}
		else if (i < 32)
		{
	    		f = (d & b) | (~d & cc);
	    		g = (5 * i + 1) % 16;
		}
		else if (i < 48)
		{
	    		f = b ^ cc ^ d;
	   		g = (3 * i + 5) % 16;
		}
		else
		{
	    		f = cc ^ (b | ~d);
	    		g = (7 * i) % 16;
		}
		temp = d;
		d = cc;
		cc = b;
		b = b + rotl32(a + f + K[i] + m[g], S[i]);
		a = temp;
	}
    	c->a += a;
    	c->b += b;
    	c->c += cc;
	c->d += d;
}
