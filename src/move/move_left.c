#include "cub3d.h"

void	move_left(t_overall *x)
{
	float offset_x;
	float offset_y;

	offset_y = 0;
	offset_x = -0.05;
	if (check_pos(x, offset_x, offset_y))
		return ;
	x->map->hero_x += offset_x;
	x->map->hero_y += offset_y;
}
