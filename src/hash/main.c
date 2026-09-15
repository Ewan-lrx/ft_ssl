#include "hash_include.h"

void	init_flags(t_flags *flags)
{
	flags->p_flag = 0;
	flags->q_flag = 0;
	flags->r_flag = 0;
	flags->s_flag = 0;
	flags->inputs = NULL;
	flags->input_count = 0;
}

int	cmd_md5(int argc, char **argv)
{
	t_hash_algo	algo;
	t_flags		flags;
	int			ret;

	algo.init = md5_init;
	algo.update = md5_update;
	algo.final = md5_final;
	algo.digest_size = 16;
	init_flags(&flags);
	if (parse_args(argc, argv, &flags))
		return (1);
	ret = process_command(&algo, &flags, "MD5", "md5");
	free(flags.inputs);
	return (ret);
}

int	cmd_sha256(int argc, char **argv)
{
	t_hash_algo	algo;
	t_flags		flags;
	int			ret;

	algo.init = sha256_init;
	algo.update = sha256_update;
	algo.final = sha256_final;
	algo.digest_size = 32;
	init_flags(&flags);
	if (parse_args(argc, argv, &flags))
		return (1);
	ret = process_command(&algo, &flags, "SHA256", "sha256");
	free(flags.inputs);
	return (ret);
}

int	cmd_whirlpool(int argc, char **argv)
{
	t_hash_algo	algo;
	t_flags		flags;
	int			ret;

	algo.init = whirlpool_init;
	algo.update = whirlpool_update;
	algo.final = whirlpool_final;
	algo.digest_size = 64;
	init_flags(&flags);
	if (parse_args(argc, argv, &flags))
		return (1);
	ret = process_command(&algo, &flags, "WHIRLPOOL", "whirlpool");
	free(flags.inputs);
	return (ret);
}

int	process_command(t_hash_algo *algo, t_flags *flags, char *label, char *cmd)
{
	int	i;
	int	ret;

	ret = 0;
	if (flags->p_flag)
		ret |= hash_stdin_p(algo, flags, label);
	if (flags->input_count > 0)
	{
		i = 0;
		while (i < flags->input_count)
		{
			if (flags->inputs[i].type == INPUT_STRING)
				ret |= hash_string(algo, flags, label, flags->inputs[i].value);
			else
				ret |= hash_file(algo, flags, label, cmd, flags->inputs[i].value);
			i++;
		}
	}
	else if (!flags->p_flag)
		ret |= hash_stdin_default(algo, flags, label);
	return (ret);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_printf("usage: ft_ssl command [flags] [file/string]\n");
		return (1);
	}
	return (dispatch(argv[1], argc, argv));
}
