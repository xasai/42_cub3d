#include "cub3d.h"
#define FOV 0.66f

void	draw_rays_3d(t_overall *z)
{
	size_t i;
	t_ray ray;
	float acos;
	float asin;

	i = 0;
	while (i < z->conf->res_x)
	{
		ray.angle = z->map->hero_a - FOV / 2 + FOV * i / (float)(z->conf->res_x); 
		ray.distance= 0;
		acos = cos(ray.angle);
		asin = sin(ray.angle);
		while (ray.distance < 15)
		{
			ray.cx = z->map->hero_x + ray.distance * acos;
			ray.cy = z->map->hero_y + ray.distance * asin;
			if (z->map->matrix[(int)ray.cy][(int)ray.cx] != '0')
			{
				draw_ray(z, ray, i);
				break ;
			}
			ray.distance += 0.005;
		}
		i++;
	}
}

void	draw_ray(t_overall *z, t_ray ray, size_t i)
{
	size_t line_height;
	float hitx;
	float hity;
	int x_textr; 

	line_height = z->conf->res_y / (ray.distance * cos(ray.angle - z->map->hero_a));
	z->pxx = i;
	z->pxy = z->conf->res_y / 2 - line_height / 2;
	hitx = ray.cx - floor(ray.cx + 0.5);
	hity = ray.cy - floor(ray.cy + 0.5);
	x_textr = hitx * z->nswe_img[0]->size_x;
	if (fabs(hity) > fabs(hitx))
		x_textr = hity * z->nswe_img[0]->size_x;
	if (x_textr < 0)
		x_textr += z->nswe_img[0]->size_x;
	texture_line(z->nswe_img[0], z, line_height, x_textr);
	if (line_height < (size_t)z->conf->res_y - 1)
		fill_updown(z, line_height);
}
