#include "hash_include.h"


void	print_error(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	print_hex(uint8_t *digest, size_t len)
{
	static const char       hex[] = "0123456789abcdef";
	size_t                          i;

	i = 0;
	while (i < len)
	{
		ft_putchar_fd(hex[(digest[i] >> 4) & 0xF], 1);
		ft_putchar_fd(hex[digest[i] & 0xF], 1);
		i++;
	}
}

int	count_inputs(int argc, char **argv)
{
	int     i;
	int     count;
	int     stop_flags;

	i = 2;
	count = 0;
	stop_flags = 0;
	while (i < argc)
	{
		if (!stop_flags && ft_strcmp(argv[i], "-s") == 0)
		{
			count++;
			i++;
		}
		else if (!stop_flags && (ft_strcmp(argv[i], "-p") == 0
					|| ft_strcmp(argv[i], "-q") == 0
					|| ft_strcmp(argv[i], "-r") == 0))
		{
		}
		else
		{
			stop_flags = 1;
			count++;
		}
		i++;
	}
	return (count);
}

void	print_result(t_flags *flags, char *label, uint8_t *digest,
		size_t len, char *source, int is_file)
{
	if (flags->q_flag)
	{
		print_hex(digest, len);
		ft_printf("\n");
		return ;
	}
	if (!flags->r_flag)
	{
		if (is_file)
			ft_printf("%s (%s) = ", label, source);
		else
			ft_printf("%s (\"%s\") = ", label, source);
		print_hex(digest, len);
	}
	else
	{
		print_hex(digest, len);
		if (is_file)
			ft_printf(" %s", source);
		else
			ft_printf(" \"%s\"", source);
	}
	ft_printf("\n");
}

