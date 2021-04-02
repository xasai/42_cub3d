#include "cub3d.h"

int		check_pos(t_overall *x, float offset_x, float offset_y)
{
	char ch;

	ch = x->map->matrix[(int)(x->map->hero_y + offset_y)]
		[(int)(x->map->hero_x + offset_x)];
	return ((ch == '1') + (ch == '2'));
}
