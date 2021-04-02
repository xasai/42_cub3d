#include "cub3d.h"

int	do_graphic_shit(t_overall *x)
{
	t_img	*img;

	if (x->img)
		mlx_destroy_image(x->mlx, x->img->img);
	img = init_image(x);
	if (img->img == NULL)
		exit_error("When alloc memory", x->conf, 5);
	fill_img(x, x->conf->ceiling);
	print_minimap(x);
	mlx_put_image_to_window(x->mlx, x->win, img->img, 0, 0);
	return (0);
}

void	put_pixel(t_img *data, int pos_x, int pos_y, int rgb)
{
	char	*dst;

	dst = data->addr + (pos_y * data->line_len + pos_x * (data->bpp / 8));
	*(unsigned int *)dst = rgb;
}

void	fill_row(t_overall *x, int pos_y, int rgb)
{
	int i;
	
	i = -1;
	while (x->conf->res_x > ++i)
		put_pixel(x->img, i, pos_y, rgb);
}

void	fill_img(t_overall *x, int rgb)
{
	int *ip;
	int k;

	ip = (int *)x->img->addr;
	k = x->conf->res_x * x->conf->res_y;
	while (k--)
		ip[k] = rgb;
}

void	draw_rectangle(t_overall *x, int sizex, int sizey, int rgb)
{
	int i;

	while (sizey--)
	{
		i = sizex;
		while (i--)
			put_pixel(x->img, x->px.cur_x + i, x->px.cur_y + sizey, rgb);
	}
}

