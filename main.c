#include "include.h"

int	check_args(int argc, char **argv)
{
	if (argc == 2)
		return (ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\nCommands:\nmd5\nsha256\n\nFlags:\n-p -q -r -s\n", argv[1]));
	if (argc == 1)
		return (ft_printf("usage: ft_ssl command [flags] [file/string]\n"));
	return (0);
}

int	main(int argc, char **argv)
{
	if (check_args(argc, argv))
		return (1);
	ft_printf("END OF THE TEST\n");
}
