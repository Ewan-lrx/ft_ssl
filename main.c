#include "include.h"

void	init_flags(t_flags *flags)
{
	flags->p_flag = 0;
	flags->q_flag = 0;
	flags->r_flag = 0;
	flags->s_flag = 0;
}

int	check_args(int argc, char **argv, f_flags *flags)
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

int	main(int argc, char **argv)
{
	t_flags	flags;
	init_flags(&flags);
	if (check_args(argc, argv))
		return (1);
	ft_printf("END OF THE TEST\n");
}
