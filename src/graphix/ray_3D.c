#include "cub3d.h"

void	draw_ray_2d(t_overall *z)
{
	float ray_a;
	size_t i;
	size_t line_height;

	i = 0;
	while (i < z->conf->res_x)
	{
		ray_a = z->map->hero_a -  0.66 / 2 + 0.66 * i / (float)(z->conf->res_x); 
		for (double c=0;c < 10; c+=0.0005)
		{
			float x = z->map->hero_x + c*cos(ray_a);
			float y = z->map->hero_y + c*sin(ray_a);
			if (z->map->matrix[(int)y][(int)x] != '0')
			{
				line_height = z->conf->res_y / (c * cos(ray_a - z->map->hero_a));
				//printf("(%u / %f) = %lu\n", z->conf->res_y, c, line_height);
				z->pxx = i;
				z->pxy = z->conf->res_y / 2 - line_height / 2;
				v_line(z, line_height, 0xac18de); 
				break;
			}
			//put_pixel(z->img, x * 32, y * 32, 0xff0000);
		}
		i++;
	}
}
