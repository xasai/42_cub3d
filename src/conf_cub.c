#include "cub3d.h"

void	config_init(t_flags **conf)
{
	if (!(*conf = ft_calloc(sizeof(**conf), 1)))
		exit_error("In function 'config_init' when allocate memory", 3);
}
