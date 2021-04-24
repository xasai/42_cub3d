#include "cub3d.h"

int	do_graphic_shit(t_overall *x)
{
	t_img	*x_img;

	x_img = x->x_img;
	if (x_img->img == NULL)
		exit_error("When alloc memory", x->conf, 5);
	fill_img(x_img, x->conf->ceiling);	
	print_minimap(x);
	mlx_put_image_to_window(x->mlx, x->win, x_img->img, 0, 0);
	return (0);
}

void	put_pixel(t_img *data, int pos_x, int pos_y, int rgb)
{
	char	*dst;

	if (pos_x < 0 || pos_y < 0)
		return ;
	dst = data->addr + (pos_y * data->line_len + pos_x * (data->bpp / 8));
	*(unsigned int *)dst = rgb;
}

void	fill_row(t_img *img, int pos_y, int rgb)
{
	int i;
	
	i = -1;
	while (img->line_len > ++i)
		put_pixel(img, i, pos_y, rgb);
}

void	fill_img(t_img *img, int rgb)
{
	int *ip;
	int k;

	ip = (int *)img->addr;
	k = img->size / 4;
	while (k--)
		ip[k] = rgb;
}

void	draw_rectangle(t_img *x, int sizex, int sizey, int rgb)
{
	int i;

	while (sizey--)
	{
		i = sizex;
		while (i--)
			put_pixel(x, x->pxx + i, x->pxy + sizey, rgb);
	}
}

