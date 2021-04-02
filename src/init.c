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
	//mlx_loop_hook(x.mlx, do_graphic_shit, &x);
	mlx_loop(x.mlx);
}

void	init_conf(t_conf **conf)
{
	*conf = ft_calloc(sizeof(t_conf), 1);
	if (!*conf)
		exit_error("When allocate memory", *conf, 2);
	(*conf)->map = ft_calloc(sizeof(t_map), 1);
	if (!(*conf)->map)
		exit_error("When allocate memory", *conf, 2);
}

t_img 	*init_image(t_overall *x)
{
	x->img = ft_calloc(sizeof(t_img), 1);
	if (!x->img)
		exit_error("When allocate memory", x->conf, 2); //conf, map, mlx ................
	x->img->img = mlx_new_image(x->mlx, x->conf->res_x, x->conf->res_y);
	x->img->addr = mlx_get_data_addr(x->img->img, &x->img->bpp,
			&x->img->line_len, &x->img->endian);
	return (x->img);
}

void	init_resolution(t_overall *x)
{
	int sizex;
	int sizey;
	int *cur_y;
	int *cur_x;

	mlx_get_screen_size(x->mlx, &sizex, &sizey);
	cur_y = &x->conf->res_y;
	cur_x = &x->conf->res_x;
	if (sizex < *cur_y || sizey < *cur_y
		|| *cur_y < 480 || *cur_x < 680) 
	{
		*cur_y = sizey;
		*cur_x = sizex;
	}
	x->scale = 1; //FIXME INITIALIZING SCALE HERE
}

void	init_hook(t_overall *x)
{
	mlx_hook(x->win, 2, 1L<<0, close_x, x);
	mlx_hook(x->win, 2, 1L<<0, move, x);
}
