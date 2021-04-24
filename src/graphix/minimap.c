#include "cub3d.h"

void	print_minimap(t_overall *x)
{
	int		i;
	int		k;
	
	i = -1;
	init_image(&x->m_img, x, 20 * x->scale * x->map->x, \
							 20 * x->scale * x->map->y);
	while (++i < (int)x->map->y)
	{
		k = -1;	
		while (x->map->matrix[i][++k])
		{
			if (x->map->matrix[i][k] == '1')	
				print_map_square(x,	0x000000); 
			else if (x->map->matrix[i][k] == '0')
				print_map_square(x,	0xffffff); 
			else if (x->map->matrix[i][k] == '2')
				print_map_square(x,	0xff0000); 
			x->m_img->pxx += (20 * x->scale);
		}
		x->m_img->pxx = 0;
		x->m_img->pxy += 20 * x->scale;
	}
	print_hero(x);
	mm_dir(x);
	ft_memcpy(x->x_img->addr, x->m_img->addr, x->m_img->size);
}

void 	mm_dir(t_overall *x)
{
	float px;
	float py;
	float dx;
	float dy;

	px = x->map->hero_x * 20 * x->scale;
	py = x->map->hero_y * 20 * x->scale;
	dx = x->map->hero_dx;
	dy = x->map->hero_dy;
	printf("\e[1;95m\t\t\t\t<DIR X> [%f]  <DIR Y> [%f]\e[0m\n", dx, dy); 
	for (int i = 0; i < 20; i +=1)
		put_pixel(x->m_img, px + dx * i, py + dy * i, 0x00ff00);
}

void	print_hero(t_overall *x)
{
	size_t	size;	

	size = 5 * x->scale;
	printf("\e[1;35m\t\t\t\thero %.3f %.3f\e[0m\n", x->map->hero_x, x->map->hero_y);
	x->m_img->pxx = x->map->hero_x * (20 * x->scale) - size / 2;
	x->m_img->pxy = x->map->hero_y * (20 * x->scale) - size / 2;
	draw_rectangle(x->m_img, size, size, 0x04ffff); 
}

void	print_map_square(t_overall *x, int rgb)
{
	int i;
	int k;
	int px;

	px = 20 * x->scale;
	i = -1;
	k = 0;
	while (++i < px)
		put_pixel(x->m_img, x->m_img->pxx + i, x->m_img->pxy + k, 0x00);
	while (++k < px)
	{
		i = -1;
		while (++i < px)
		{
			if (px - 1 == i)
				put_pixel(x->m_img, x->m_img->pxx + i, x->m_img->pxy + k, 0x00);
			else 
				put_pixel(x->m_img, x->m_img->pxx + i, x->m_img->pxy + k, rgb);
		}
	}
	i = -1;
	while (++i < px)
		put_pixel(x->m_img, x->m_img->pxx + i, x->m_img->pxy + k, 0x00);
}
