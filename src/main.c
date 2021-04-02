#include "cub3d.h"
int	main(int ac, char **av)
{
	handle_args(ac, av);
	init(ac, av);
	return (0);
}

/*
** ret  value
** 1 => just exit and print error message		<|
** 2 => problem with allocation					<|
** 3 =>	.cub file error, also clear struct 		<|
** 4 =>	map error, also clear struct and list	<|
** 5 => 4 + clear matrix						<|
*/
void	exit_error(char *str, t_conf *conf, int ret)
{
	char	*tmp;

	write(2, "Erorr\ncub3D: ", 13);
	if (ret == 3)
		write(2, "When reading .cub: ", 19);
	write(2, str, ft_strlen(str));
	if (ret == 3 || ret == 0)
	{
		write(2, " (line ", 7);
		tmp = ft_itoa(conf->line_num);
		write(2, tmp, ft_strlen(tmp));
		write(2, ")", 1);
	}
	write(2, "\n", 1);
	exit(ret);
}
