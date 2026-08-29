#include "hash_include.h"

int	hash_stdin_p(t_hash_algo *algo, t_flags *flags, char *label)
{
	void    *ctx;
	uint8_t *digest;
	uint8_t *content;
	size_t  cap;
	size_t  len;
	uint8_t buf[4096];
	ssize_t n;

	(void)label;
	cap = 4096;
	len = 0;
	content = malloc(cap);
	if (!content)
		return (1);
	ctx = malloc(2048);
	digest = malloc(algo->digest_size);
	algo->init(ctx);
	while ((n = read(0, buf, sizeof(buf))) > 0)
	{
		if (len + (size_t)n > cap)
		{
			cap *= 2;
			content = realloc(content, cap);
		}
		ft_memcpy(content + len, buf, n);
		len += n;
		algo->update(ctx, buf, n);
	}
	algo->final(ctx, digest);
	if (len > 0 && content[len - 1] == '\n')
		len--;
	if (flags->q_flag)
	{
		write(1, content, len);
		ft_printf("\n");
	}
	else
	{
		ft_printf("(\"");
		write(1, content, len);
		ft_printf("\")= ");
	}
	print_hex(digest, algo->digest_size);
	ft_printf("\n");
	free(content);
	free(ctx);
	free(digest);
	return (0);
}

int	hash_stdin_default(t_hash_algo *algo, t_flags *flags, char *label)
{
	void    *ctx;
	uint8_t *digest;
	uint8_t buf[4096];
	ssize_t n;

	(void)label;
	ctx = malloc(2048);
	if (!ctx)
		return (1);
	digest = malloc(algo->digest_size);
	if (!digest)
		return (1);
	algo->init(ctx);
	while ((n = read(0, buf, sizeof(buf))) > 0)
		algo->update(ctx, buf, n);
	algo->final(ctx, digest);
	if (flags->q_flag)
	{
		print_hex(digest, algo->digest_size);
		ft_printf("\n");
	}
	else
	{
		ft_printf("(stdin)= ");
		print_hex(digest, algo->digest_size);
		ft_printf("\n");
	}
	free(ctx);
	free(digest);
	return (0);
}


int	hash_file(t_hash_algo *algo, t_flags *flags, 
		  char *label, char *cmd, char *filename)
{
	void    *ctx;
	uint8_t *digest;
	int             fd;
	uint8_t buf[4096];
	ssize_t n;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("ft_ssl: %s: %s: No such file or directory\n", cmd, filename);
		return (1);
	}
	ctx = malloc(2048);
	if (!ctx)
		return (1);
	digest = malloc(algo->digest_size);
	if (!digest)
		return (1);
	algo->init(ctx);
	while ((n = read(fd, buf, sizeof(buf))) > 0)
		algo->update(ctx, buf, n);
	algo->final(ctx, digest);
	print_result(flags, label, digest, algo->digest_size, filename, 1);
	close(fd);
	free(ctx);
	free(digest);
	return (0);
}


int	hash_string(t_hash_algo *algo, t_flags *flags, char *label, char *str)
{
	void    *ctx;
	uint8_t *digest;

	ctx = malloc(2048);
	if (!ctx)
		return (1);
	digest = malloc(algo->digest_size);
	if (!digest)
		return (1);
	algo->init(ctx);
	algo->update(ctx, (uint8_t *)str, ft_strlen(str));
	algo->final(ctx, digest);
	print_result(flags, label, digest, algo->digest_size, str, 0);
	free(ctx);
	free(digest);
	return (0);
}
