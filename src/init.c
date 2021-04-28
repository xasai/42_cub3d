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
	init_image(&(x.img), &x, x.conf->res_x, x.conf->res_y); x.win = mlx_new_window(x.mlx, x.conf->res_x, x.conf->res_y, "cub3D");
	load_textures(&x);
	init_hook(&x);
	fill_img(&x, x.conf->ceiling);
	do_graphic_shit(&x);
	mlx_loop(x.mlx);
}

void	init_hook(t_overall *x)
{
	mlx_hook(x->win, 2, 1L << 0, close_x, x);
	mlx_hook(x->win, 2, 1L << 0, key_handler, x);
}

/*
** These two functions load all 4 NSWE textures to struct nswe_img[4]
*/

void load_textures(t_overall *x)
{
	char *path[4];
	int		i;

	i = -1;
	path[0] = x->conf->no;
	path[1] = x->conf->so;
	path[2] = x->conf->we;
	path[3] = x->conf->ea;
	while (++i < 4)
		file_to_img(&(x->nswe_img[i]), path[i], x);
}

void file_to_img(t_img **img_ptr, char *path, t_overall *x)
{
	void  *img;
	int   size_x;
	int	  size_y;
	
	size_x = ft_strlen(path);
	size_y = 0;
	img = NULL;
	if (!ft_strncmp(&path[size_x - 4], ".xpm", 5))
		img = mlx_xpm_file_to_image(x->mlx, path, &size_x, &size_x);
	else
		exit_error("Wrong texture file extension", x->conf, 999);
	if (!img)
		exit_error("When opening texture files", x->conf, 0x10);
	*img_ptr = ft_calloc(sizeof(t_img), 1);
	if (!*img_ptr) 
		exit_error("When alloca in file_to_img files", x->conf, 0xff01);
	(*img_ptr)->img = img;
	(*img_ptr)->addr = mlx_get_data_addr((*img_ptr)->img, \
								&(*img_ptr)->bpp, &(*img_ptr)->line_len, \
								&(*img_ptr)->endian);
	(*img_ptr)->size = size_x * size_y;
	(*img_ptr)->size_x = size_x;
	(*img_ptr)->size_y = size_y;
}
