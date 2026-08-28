#include "include.h"

void sha256_init(void *context)
{
     	t_sha256_context *c;
    
	c = (t_sha256_context *)context;
    	c->h[0] = 0x6a09e667;
    	c->h[1] = 0xbb67ae85;
    	c->h[2] = 0x3c6ef372;
    	c->h[3] = 0xa54ff53a;
    	c->h[4] = 0x510e527f;
    	c->h[5] = 0x9b05688c;
    	c->h[6] = 0x1f83d9ab;
    	c->h[7] = 0x5be0cd19;
    	c->buffer_len = 0;
    	c->total_len = 0;
}

void	sha256_update(void *context, uint8_t *data, size_t len)
{
    	t_sha256_context *c;
    	size_t to_copy;
    
	c = (t_sha256_context *)context;
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
	    		sha256_process_block(c, c->buffer);
	    		c->buffer_len = 0;
		}
    	}
}

void	sha256_process_block(void *context, uint8_t data[64])
{
	uint32_t	w[64];
	int		i;
	t_sha256_context	*c;
	uint32_t	s0, s1, a, b, cc, d, e, f, g, h;
	uint32_t	S1, ch, temp1, S0, maj, temp2;

	c = (t_sha256_context *)context;
	for (i = 0; i < 16; i++)
	{
		w[i] = ((uint32_t)data[i * 4] << 24)
			| ((uint32_t)data[i * 4 + 1] << 16)
			| ((uint32_t)data[i * 4 + 2] << 8)
			| ((uint32_t)data[i * 4 + 3]);
	}
	for (i = 16; i < 64; i++)
	{
		s0 = rotr32(w[i - 15], 7) ^ rotr32(w[i - 15], 18) ^ (w[i - 15] >> 3);
		s1 = rotr32(w[i-2], 17) ^ rotr32(w[i-2], 19) ^ (w[i-2] >> 10);
	    	w[i] = w[i-16] + s0 + w[i-7] + s1;
	}
	a = c->h[0];
	b = c->h[1];
	cc = c->h[2];
	d = c->h[3];
	e = c->h[4];
	f = c->h[5];
	g = c->h[6];
	h = c->h[7];
	for (i = 0; i < 64; i++)
	{
		S1 = rotr32(e, 6) ^ rotr32(e, 11) ^ rotr32(e, 25);
		ch = (e & f) ^ (~e & g);
		temp1 = h + S1 + ch + K256[i] + w[i];
		S0 = rotr32(a, 2) ^ rotr32(a, 13) ^ rotr32(a, 22);
		maj = (a & b) ^ (a & cc) ^ (b & cc);
		temp2 = S0 + maj;
		h = g;
		g = f;
		f = e;
		e = d + temp1;
		d = cc;
		cc = b;
		b = a;
		a = temp1 + temp2;
	}
	c->h[0] += a;
	c->h[1] += b;
	c->h[2] += cc;
	c->h[3] += d;
	c->h[4] += e;
	c->h[5] += f;
	c->h[6] += g;
	c->h[7] += h;
}

void	sha256_final(void *context, uint8_t *digest)
{
	t_sha256_context	*c;
	uint64_t		bits_len;
	size_t			padding_len;
	uint8_t			padding[64];
	uint8_t			size_buffer[8];
	int			i;

	c = (t_sha256_context *)context;
	bits_len = c->total_len * 8;
	ft_memset(padding, 0, 64);
	padding[0] = 0x80;
	if (c->buffer_len < 56)
		padding_len = 56 - c->buffer_len;
	else
		padding_len = 64 + 56 - c->buffer_len;
	sha256_update(c, padding, padding_len);
	for (i = 0; i < 8; i++)
		size_buffer[i] = (uint8_t)(bits_len >> ((7 - i) * 8));
	sha256_update(c, size_buffer, 8);
	for (i = 0; i < 8; i++)
	{
		digest[i * 4] = (uint8_t)(c->h[i] >> 24);
		digest[i * 4 + 1] = (uint8_t)(c->h[i] >> 16);
		digest[i * 4 + 2] = (uint8_t)(c->h[i] >> 8);
		digest[i * 4 + 3] = (uint8_t)(c->h[i]);
	}
}
