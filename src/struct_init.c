#include "cub3d.h"

void	init_conf(t_conf **conf)
{
	*conf = ft_calloc(sizeof(t_conf), 1);
	if (!*conf)
		exit_error("When allocate memory", *conf, 2);
	(*conf)->map = ft_calloc(sizeof(t_map), 1);
	if (!(*conf)->map)
		exit_error("When allocate memory", *conf, 2);
}

void 	init_image(t_img **img_ptr, t_overall *x, \
		uint16_t size_x, uint16_t size_y)
{
	*img_ptr = ft_calloc(sizeof(t_img), 1);
	if (!*img_ptr)
		exit_error("When allocate memory", x->conf, 2);
	(*img_ptr)->img = mlx_new_image(x->mlx, size_x, size_y);
	(*img_ptr)->addr = mlx_get_data_addr((*img_ptr)->img, \
						&(*img_ptr)->bpp, &(*img_ptr)->line_len, \
						&(*img_ptr)->endian);
	(*img_ptr)->size = (size_t)(size_y * size_x) * ((*img_ptr)->bpp / 8);
}

/*
** FIXME SCALE
*/
void	init_resolution(t_overall *x)
{
	int			sizex;
	int			sizey;
	uint16_t	*cur_y;
	uint16_t	*cur_x;

	mlx_get_screen_size(x->mlx, (int *)&sizex, &sizey);
	cur_y = &x->conf->res_y;
	cur_x = &x->conf->res_x;
	if ((uint16_t)sizex < *cur_y || (uint16_t)sizey < *cur_y
		|| *cur_y < 480 || *cur_x < 640)
	{
		*cur_y = sizey;
		*cur_x = sizex;
	}
	x->scale = 1;
}
