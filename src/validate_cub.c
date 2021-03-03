#include "cub3d.h"

void		validate_path(char *path, t_conf *conf)
{
	char *p;
	
	p = path;
	while (ft_isprint(*p))
		p++;
	while (ft_isspace(*p))
		p++;
	if (*p)
		exit_error("When reading .cub file: bad texture path", conf, 3);	
}
