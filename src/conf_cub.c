#include "cub3d.h"

void	config_init(t_conf **conf)
{
	if (!conf || !(*conf = ft_calloc(sizeof(**conf), 1)) ||
			!((*conf)->map = ft_calloc(sizeof((*conf)->map), 1)))
		exit_error("In function 'config_init' when allocate memory", *conf, 2);
}

