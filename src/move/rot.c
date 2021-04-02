#include "cub3d.h"

void	rot_l(t_overall *x)
{
	x->map->hero_a -= PI / 20;
	if (x->map->hero_a > PI * 2)
		x->map->hero_a -= 2 * PI;
	else if (x->map->hero_a < PI * -2)
		x->map->hero_a += 2 * PI;
}

void	rot_r(t_overall *x)
{
	x->map->hero_a += PI / 20;
	if (x->map->hero_a > PI * 2)
		x->map->hero_a -= 2 * PI;
	else if (x->map->hero_a < PI * -2)
		x->map->hero_a += 2 * PI;
}
