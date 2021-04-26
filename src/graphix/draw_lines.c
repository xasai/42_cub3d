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
