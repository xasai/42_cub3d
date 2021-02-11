#include "cub3d.h"

void				read_cub(int ac, char **av)
{
	int				ret;
	int				fd;
	char			*line;
	t_flags 		*config;

	config_init(&config);
	fd = open(av[1], O_RDONLY);
	if (fd < 3)
		exit_error("When trying to open file", config, 1);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		parse_cub(line, config);
		free(line);
	}
	if (ret < 0)
		exit_error("When reading .cub file", config, 2);
	if (ac == 3)
		config->option = 1;
}
