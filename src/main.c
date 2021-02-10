#include "cub3d.h"

int		main(int ac, char **av)
{
	handle_args(ac, av);
	read_cub(ac, av);
	return (0);
}

void		handle_args(int ac, char **av)
{
	int		len;

	if (ac > 3 || ac < 2)
		exit_error("Wrong number of arguments", 1);
	else if (ac >= 2)
	{
		len = ft_strlen(av[1]);
		if (len < 4)
			exit_error("Invalid 1st argument", 1);
		else if (ft_strncmp(".cub", &av[1][len - 4], 5))
			exit_error("Invalid 1st argument", 1);
	}
	if (ac == 3 && ft_strncmp("--save", av[2], 7))
		exit_error("Invalid option: Try '--save'", 1);
}

void	exit_error(char *str, int ret)
{
	write(2, "Erorr\ncub3D: ", 13);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(ret);
}
