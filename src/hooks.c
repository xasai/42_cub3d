#include "cub3d.h"

int	close_x(int keycode, t_overall *x)
{
	printf("KEY - %d\n", keycode);	
	if ((char)keycode == 'q' || 0xff1b == keycode)
		mlx_destroy_window(x->mlx, x->win);
	return (0);
}

int key_handler(int keycode, t_overall *x)
{
	printf("\t\t\t\t\t\e[1;32mKEY [%d]\e[0m\n", keycode);
	if (keycode == K_W || keycode == K_AR_U)
		move_forward(x);
	else if (keycode == K_S || keycode == K_AR_D)
		move_backward(x);
	else if (keycode == K_A || keycode == K_AR_L)
		rot_l(x);
	else if (keycode == K_D || keycode == K_AR_R)
		rot_r(x);
	else if (keycode == K_ESC)
		exit(0); // FIXME clear after yourself
	do_graphic_shit(x);
	return (0);
}

