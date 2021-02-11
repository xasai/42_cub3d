#include "cub3d.h"

void		validate_path(char *path, t_flags *config)
{
	char *p;
	
	p = path;
	while (ft_isprint(*p))
		p++;
	while (ft_isspace(*p))
		p++;
	if (*p)
		exit_error("When reading .cub file: bad texture path", config, 3);	
}
