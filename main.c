#include "include.h"

static t_command 	g_commands[] = {
    	{"md5", cmd_md5},
    	{"sha256", cmd_sha256},
    	{NULL, NULL}
};

void	init_flags(t_flags *flags)
{
	flags->p_flag = 0;
	flags->q_flag = 0;
	flags->inputs = NULL;
	flags->r_flag = 0;
	flags->s_flag = 0;
}

int	count_inputs(int argc, char **argv)
{
	int	i;
	int	count;

	i = 2;
	count = 0;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-s") == 0)
		{
			count++;
			i++;
		}
		else if (ft_strcmp(argv[i], "-p") == 0
			|| ft_strcmp(argv[i], "-q") == 0
			|| ft_strcmp(argv[i], "-r") == 0)
			{
			}
		else
			count++;
		i++;
	}
	return (count);
}

int	parse_args(int argc, char **argv, t_flags *flags)
{
	int	i;
	int	idx;

	flags->input_count = count_inputs(argc, argv);
	flags->inputs = malloc(sizeof(t_input) * flags->input_count);
	if (!flags->inputs)
		return(1);
	i = 2;
	idx = 0;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-p") == 0)
			flags->p_flag = 1;
		else if (ft_strcmp(argv[i], "-q") == 0)
			flags->q_flag = 1;
		else if (ft_strcmp(argv[i], "-r") == 0)
			flags->r_flag = 1;
		else if (ft_strcmp(argv[i], "-s") == 0)
		{
			i++;
			if (i >= argc)
			{
				ft_printf("ft_ssl: option requires an argument: '-s'\n");
				return(1);
			}
			flags->inputs[idx].type = INPUT_STRING;
			flags->inputs[idx].value = argv[i];
			idx++;
			flags->s_flag = 1;
		}
		else
		{
			flags->inputs[idx].type = INPUT_FILE;
			flags->inputs[idx].value = argv[i];
			idx++;
		}
		i++;
	}
	return (0);
}

int	check_args(int argc, char **argv, t_flags *flags)
{
	int	i;

	i = 0;
	if (argc == 2)
		return (ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\nCommands:\nmd5\nsha256\n\nFlags:\n-p -q -r -s\n", argv[1]));
	if (argc == 1)
		return (ft_printf("usage: ft_ssl command [flags] [file/string]\n"));
	while (argv[i])
	{
		if (ft_memcmp(argv[i], "-s", 3) == 0 && argc >= i + 1)
			flags->s_flag = 1;
		if (ft_memcmp(argv[i], "-q", 3) == 0)
			flags->q_flag = 1;
		if (ft_memcmp(argv[i], "-r", 3) == 0)
			flags->r_flag = 1;
		if (ft_memcmp(argv[i], "-p", 3) == 0)
			flags->p_flag = 1;
		i++;
	}
	return (0);
}

int	dispatch(char *cmd_name, int argc, char **argv)
{
	int	i;

	i = 0;
	while (g_commands[i].name)
	{
		if (ft_strcmp(g_commands[i].name, cmd_name) == 0)
			return (g_commands[i].func(argc, argv));
		i++;
	}
	ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n", cmd_name);
    	ft_printf("Commands:\nmd5\nsha256\n\nFlags:\n-p -q -r -s\n");
    	return (1);
}

int	cmd_md5(int argc, char **argv)
{
	t_hash_algo	algo;
	t_flags		flags;
	int		ret;

	algo.init = md5_init;
	algo.update = md5_update;
	algo.final = md5_final;
	algo.digest_size = 16;
	init_flags(&flags);
	if (parse_args(argc, argv, &flags))
		return (1);
	ret = process_command(&algo, &flags, "MD5");
	free(flags.inputs);
	return (ret);
}


int 	cmd_sha256(int argc, char **argv)
{
	t_hash_algo     algo;
	t_flags         flags;
	int             ret;

	algo.init = sha256_init;
	algo.update = sha256_update;
	algo.final = sha256_final;
	algo.digest_size = 32;
	init_flags(&flags);
	if (parse_args(argc, argv, &flags))
		return (1);
	ret = process_command(&algo, &flags, "SHA256");
	free(flags.inputs);
	return (ret);
}

int	process_command(t_hash_algo *algo, t_flags *flags, char *label)
{
	int     i;
	int     ret;

	i = 0;
	ret = 0;
	if (flags->input_count == 0)
		return (hash_stdin(algo, flags, label));
	while (i < flags->input_count)
	{
		if (flags->inputs[i].type == INPUT_STRING)
			ret |= hash_string(algo, flags, label, flags->inputs[i].value);
		else
			ret |= hash_file(algo, flags, label, flags->inputs[i].value);
		i++;
	}
	return (ret);
}

int	hash_string(t_hash_algo *algo, t_flags *flags, char *label, char *str)
{
	void	*ctx;
	uint8_t	*digest;

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

int	hash_file(t_hash_algo *algo, t_flags *flags, char *label, char *filename)
{
	void	*ctx;
	uint8_t	*digest;
	int	fd;
	uint8_t	buf[4096];
	ssize_t	n;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("ft_ssl: %s: %s: No such file or directory\n", label, filename);
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

void	print_result(t_flags *flags, 
		     char *label, uint8_t *digest, 
		     size_t len, char *source, int is_file)
{
    	size_t i;
    
	if (!flags->q_flag)
	{
		if (!flags->r_flag)
		{
	    		if (is_file)
				ft_printf("%s (%s) = ", label, source);
	    		else
				ft_printf("%s (\"%s\") = ", label, source);
		}
    	}
    	i = 0;
    	while (i < len)
    	{
		ft_printf("%02x", digest[i]);
		i++;
    	}
    	if (flags->r_flag)
    	{
		if (is_file)
	    		ft_printf(" %s", source);
		else
	    		ft_printf(" \"%s\"", source);
    	}
    	ft_printf("\n");
}


int	main(int argc, char **argv)
{
	t_flags	flags;
	init_flags(&flags);
	if (check_args(argc, argv))
		return (1);
	ft_printf("END OF THE TEST\n");
}
