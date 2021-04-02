#include "cub3d.h"

void	print_minimap(t_overall *x)
{
	size_t	i;
	int		k;
	
	x->px.cur_x = 0;
	x->px.cur_y = 0;
	i = -1;
	while (++i < x->map->y)
	{
		k = -1;	
		while (x->map->matrix[i][++k])
		{
			if (x->map->matrix[i][k] == '1')	
				print_map_square(x,	0x000000); 
			else if (x->map->matrix[i][k] == '0'
				|| x->map->matrix[i][k] == x->map->hero_ch)
				print_map_square(x,	0xffffff); 
			else if (x->map->matrix[i][k] == '2')
				print_map_square(x,	0xff0000); 
			x->px.cur_x += (20 * x->scale);//SCALE
		}
		x->px.cur_x = 0;
		x->px.cur_y += 20 * x->scale; //SCALE
	}
	print_hero(x);
	mm_ray(x);
}

void	mm_ray(t_overall *x)
{
	float cx;
	float cy;

	x->px.cur_x = x->map->hero_x* (20 * x->scale);
	x->px.cur_y = x->map->hero_y* (20 * x->scale);
	float fov =  PI / 3;
	for (int i = 0;i < x->conf->res_x; i++)
	{
		float angle = x->map->hero_a - fov / 2 + fov * i / x->conf->res_x;
		for (float t=0.0; t<20.0; t+=0.05)
		{
			cx = x->map->hero_x + t*cos(angle);
			cy = x->map->hero_y + t*sin(angle);
			if (x->map->matrix[(int)cy][(int)cx] == '1'
			|| x->map->matrix[(int)cy][(int)cx] == '2') break;
			//printf("\t\t\t\t\t\t\t\e[1;35 %.3f cos x - cosy %.3f\e[0m\n", cx, cy); 
			int pix_y = cy* 20;
			int	pix_x = cx * 20;
			put_pixel(x->img, pix_x, pix_y, 0xff0000);
			//printf("%d x px y %d\n", pix_x, pix_y); 
			//printf("%f < ANGLE >\n", angle); 
		}

	}
	printf("\e[1;91m\t\t\t\t<PLAYER_ANGLE> [%f]\e[0m\n\n\n", x->map->hero_a); 
}

void	print_hero(t_overall *x)
{
	size_t	size;	

	size = 6 * x->scale;
	printf("\e[1;35m\t\t\t\thero %.3f %.3f\e[0m\n", x->map->hero_x, x->map->hero_y);
	x->px.cur_x = x->map->hero_x * (20 * x->scale) - size / 2;
	x->px.cur_y = x->map->hero_y * (20 * x->scale) - size / 2;
	draw_rectangle(x, size, size, 0x04f32f); 
}

void	print_map_square(t_overall *x, int rgb)
{
	int i;
	int k;
	int px;

	px = 20 * x->scale; //SCALE
	i = -1;
	while (++i < px)
		put_pixel(x->img, x->px.cur_x + i, x->px.cur_y, 0x00);
	k = 0;
	while (++k < px)
	{
		i = -1;
		while (++i < px)
		{
			if (px - 1 == i)
				put_pixel(x->img, x->px.cur_x + i, x->px.cur_y + k, 0x00);
			else 
				put_pixel(x->img, x->px.cur_x + i, x->px.cur_y + k, rgb);
		}
	}
	i = -1;
	while (++i < px)
		put_pixel(x->img, x->px.cur_x + i, x->px.cur_y + k, 0x00);
}
