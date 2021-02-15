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

void			validate_line(char *line, t_conf *conf)
{
	int			closed;

	closed = 0;
	while (ft_isspace(*line))
		line++;
	if (*line && *line != '1')
		exit_error("Map isn't closed in start of field", conf, 4);
	else if (!*line)
		return ;
	while (*line)
	{
		if (*line == '1')
			closed = 1;
		else if (*line == '0' || *line == '2')
			closed = 0;
		else if ((ft_strchr("NSWE", *line) && (conf->map->player = *line))
				!(closed = 0))
			conf->f.player++;
		else if ((ft_isspace(*line) && !closed) || !ft_isspace(*line))
			exit_error("Bad map", conf, 4);
		line++;
	}
	if (!closed)
		exit_error("Map should be absolutely closed with '1' character", config, 4);
}

void				valid_upndown(int y, t_conf *conf)
{
	int 			i;
	char 			**map;

	map = config->map->map;
	i = -1;
	while (map[y][++i])
	{
		if (!ft_strchr("NSEW20", map[y][i]))
			continue ;
		if (y - 1 && ft_isspace(map[y - 1][i]))
			exit_error("Map should be absolutely closed with '1' character", conf, 8);
		if (y < conf->map->map_y && ft_isspace(map[y + 1]))
			exit_error("Map should be absolutely closed with '1' character", conf, 8);
	}
}
