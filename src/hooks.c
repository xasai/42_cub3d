#include "cub3d.h"

int	close_x(int keycode, t_overall *x)
{
	printf("KEY - %d\n", keycode);	
	if ((char)keycode == 'q' || 0xff1b == keycode)
		mlx_destroy_window(x->mlx, x->win);
	return (0);
}

int move(int keycode, t_overall *x)
{
	printf("\t\t\t\t\t\e[1;32mKEY [%d]\e[0m\n", keycode);
	if ((char)keycode == 'w' || keycode == 65362)
		move_forward(x);
	else if ((char)keycode == 's' || keycode == 65364)
		move_backward(x);
	else if ((char)keycode == 'a')
		move_left(x);
	else if ((char)keycode == 'd')
		move_right(x);
	else if (keycode == 65361) 
		rot_l(x);
	else if (keycode == 65363) 
		rot_r(x);
	do_graphic_shit(x);
	return (0);
}

