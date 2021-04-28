#include "cub3d.h"

void	print_minimap(t_overall *x)
{
	size_t	i;
	int		k;
	
	x->pxx = 0;
	x->pxy = 0;
	i = -1;
	while (++i < x->map->y)
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
			x->pxx += (32 * x->scale);//SCALE
		}
		x->pxx = 0;
		x->pxy += 32 * x->scale; //SCALE
	}
	print_hero(x);
	mm_dir(x);
}

void 	mm_dir(t_overall *x)
{
	float px;
	float py;
	float dx;
	float dy;

	px = x->map->hero_x * 32 * x->scale;
	py = x->map->hero_y * 32 * x->scale;
	dx = x->map->hero_dx;
	dy = x->map->hero_dy;
	printf("\e[1;95m\t\t\t\t<DIR X> [%f]  <DIR Y> [%f] x->scale[%f]\e[0m\n", dx, dy, x->scale); 
	for (int i = 0; i < 20; i +=1)
		put_pixel(x->img, px + dx * i, py + dy * i, 0x00ff00);
}

void	print_hero(t_overall *x)
{
	size_t	size;	

	size = 5 * x->scale;
	printf("\e[1;35m\t\t\t\thero %.3f %.3f\e[0m\n", x->map->hero_x, x->map->hero_y);
	x->pxx = x->map->hero_x * (32 * x->scale) - size / 2;
	x->pxy = x->map->hero_y * (32 * x->scale) - size / 2;
	draw_rectangle(x, size, size, 0x04f32f); 
}

void	print_map_square(t_overall *x, int rgb)
{
	int i;
	int k;
	int px;

	px = 32 * x->scale; //SCALE
	i = -1;
	while (++i < px)
		put_pixel(x->img, x->pxx + i, x->pxy, 0x00);
	k = 0;
	while (++k < px)
	{
		i = -1;
		while (++i < px)
		{
			if (px - 1 == i)
				put_pixel(x->img, x->pxx + i, x->pxy + k, 0x00);
			else 
				put_pixel(x->img, x->pxx + i, x->pxy + k, rgb);
		}
	}
	i = -1;
	while (++i < px)
		put_pixel(x->img, x->pxx + i, x->pxy + k, 0x00);
}
