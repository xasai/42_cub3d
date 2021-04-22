#include "cub3d.h"

void	init(int ac, char **av)
{
	t_overall	x;

	x = (t_overall){0};
	x.conf = read_cub(ac, av);
	x.map = x.conf->map;
	x.mlx = mlx_init();
	if (!x.mlx)
		exit_error("When allocate memory", x.conf, 2);
	init_resolution(&x);
	init_image(&x);
	x.win = mlx_new_window(x.mlx, x.conf->res_x, x.conf->res_y, "cub3D");
	init_hook(&x);
	do_graphic_shit(&x);
	mlx_loop(x.mlx);
}
