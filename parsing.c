#include "include.h"

int	parse_flags(int argc, char **argv, t_flags *flags)
{
	int	i;

	i = 2
	while (argv[i])
        {
                if (ft_memcmp(argv[i], "-s", 3) == 0 && argc >= i + 1)
                        flags->s_flag = 1;
                else if (ft_memcmp(argv[i], "-q", 3) == 0)
                        flags->q_flag = 1;
                else if (ft_memcmp(argv[i], "-r", 3) == 0)
                        flags->r_flag = 1;
                else if (ft_memcmp(argv[i], "-p", 3) == 0)
                        flags->p_flag = 1;
		else
			parse_data(
                i++;
        }
        return (0);
}

int	parse_data(int argc, char **argv, int start)
{
	while (argv[start])
	{
		if 
