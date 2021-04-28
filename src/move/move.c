#include "cub3d.h"

void	move_backward(t_overall *x)
{
	float offset_x;
	float offset_y;

	offset_x = -x->map->hero_dx * 0.30;
	offset_y = -x->map->hero_dy * 0.30;
	if (check_pos(x, offset_x, 0) 
			|| check_pos(x, 0, offset_y))
		return ;
	x->map->hero_y += offset_y;
	x->map->hero_x += offset_x;
}

void	move_forward(t_overall *x)
{
	float offset_x;
	float offset_y;

	offset_x = x->map->hero_dx * 0.30;
	offset_y = x->map->hero_dy * 0.30;
	if (check_pos(x, offset_x, 0) 
			|| check_pos(x, 0, offset_y))
		return ;
	x->map->hero_y += offset_y;
	x->map->hero_x += offset_x; 
}
