#include "cub3d.h"

#define ROT_SPEED PI / 20

void	rot_l(t_overall *x)
{
	x->map->hero_a -= ROT_SPEED;
	x->map->hero_dx = cos(x->map->hero_a);
	x->map->hero_dy = sin(x->map->hero_a);
	if (x->map->hero_a < 0)
		x->map->hero_a += 2 * PI;
}

void	rot_r(t_overall *x)
{
	x->map->hero_a += ROT_SPEED;
	x->map->hero_dx = cos(x->map->hero_a);
	x->map->hero_dy = sin(x->map->hero_a);
	if (x->map->hero_a > PI * 2)
		x->map->hero_a -= 2 * PI;
}
