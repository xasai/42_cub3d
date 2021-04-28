#include "cub3d.h"

void	v_line(t_overall *x, size_t height, int rgb)
{
	if (height + x->pxy >= x->conf->res_y)
		height = x->conf->res_y - x->pxy;
	while (height--)
		put_pixel(x->img, x->pxx, x->pxy + height, rgb);
}

void	h_line(t_overall *x, size_t lenght, int rgb)
{
	if (lenght + x->pxx >= x->conf->res_x)
		return ;
	while (lenght--)
		put_pixel(x->img, x->pxx + lenght, x->pxy, rgb);
}

void	texture_line(t_img *textr, t_overall *x, size_t height, size_t pxx)
{
	int *rgb;
	size_t y;
	size_t pxy;

	y = 0;
	while (y < height)
	{
		rgb = (int *)textr->addr;
		pxy = (y * textr->size_x) / height; 
		rgb = &rgb[pxx + pxy * textr->size_x];
		if (x->conf->res_x > x->pxx && x->pxy < x->conf->res_y)
			put_pixel(x->img, x->pxx, x->pxy + y, *rgb);
		y++;
	}
}
void	fill_updown(t_overall *x, size_t line_height)
{
	size_t height;
	x->pxy = x->conf->res_y / 2 + line_height / 2;
	height = x->conf->res_y - 1 - x->pxy;
	v_line(x, height, x->conf->floor);
	x->pxy = 0;
	v_line(x, height, x->conf->ceiling);
}	
