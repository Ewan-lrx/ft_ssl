#include "include.h"

void	sha_init(void *context)
{
	t_sha_context	*c;

	c = (t_sha_context *)context;
	c->a = 0x6a09e667;
	c->b = 0xbb67ae85;
	c->c = 0x3c6ef372;
	c->d = 0xa54ff53a;
	c->e = 0x510e527f;
	c->f = 0x9b05688c;
	c->g = 0x1f83d9ab;
	c->h = 0x5be0cd19;
	c->buffer_len = 0;
	c->total_len = 0;
	c->current_round = 0;
}


void	init_old_block(t_sha_context *context)
{
	t_data_block	*data;

	data->a = context->a;
	data->b = context->b;
	data->c = context->c;
	data->d = context->d;
	data->e = context->e;
	data->f = context->f;
	data->g = context->g;
	data->h = context->h;
}

void	sha_update(void *context, uint8_t *data)
{
	t_data_block	old_data;
	t_sha_context	*data;

	data = (t_sha_context)data;
	old_data = init_old_block(data);
	data->c = old_data->b;
	data->d = old_data->c;
	data->e = old_data->d;
	data->f = old_data->e;
	data->g = old_data->f;
	data->h = old_data->h;

}
