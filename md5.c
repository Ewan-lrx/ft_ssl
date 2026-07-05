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
