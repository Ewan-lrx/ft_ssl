#include "hash_include.h"

static t_command        g_commands[] = {
        {"md5", cmd_md5},
        {"sha256", cmd_sha256},
	{"whirlpool", cmd_whirlpool},
        {NULL, NULL}
};


int	parse_args(int argc, char **argv, t_flags *flags)
{
	int     i;
	int     idx;
	int     stop_flags;

	flags->input_count = count_inputs(argc, argv);
	flags->inputs = malloc(sizeof(t_input) * 
			(flags->input_count ? flags->input_count : 1));
	if (!flags->inputs)
		return (1);
	i = 2;
	idx = 0;
	stop_flags = 0;
	while (i < argc)
	{
		if (!stop_flags && ft_strcmp(argv[i], "-p") == 0)
			flags->p_flag = 1;
		else if (!stop_flags && ft_strcmp(argv[i], "-q") == 0)
			flags->q_flag = 1;
		else if (!stop_flags && ft_strcmp(argv[i], "-r") == 0)
			flags->r_flag = 1;
		else if (!stop_flags && ft_strcmp(argv[i], "-s") == 0)
		{
			i++;
			if (i >= argc)
			{
				ft_printf("ft_ssl: option requires an argument: '-s'\n");
				return (1);
			}
			flags->s_flag = 1;
			flags->inputs[idx].type = INPUT_STRING;
			flags->inputs[idx].value = argv[i];
			idx++;
		}
		else
		{
			stop_flags = 1;
			flags->inputs[idx].type = INPUT_FILE;
			flags->inputs[idx].value = argv[i];
			idx++;
		}
		i++;
	}
	return (0);
}

int	dispatch(char *cmd_name, int argc, char **argv)
{
	int     i;

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

