#include "cub3d.h"

void		validate_path(char *path, t_conf *conf)
{
	char 	*p;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_error("Could not open texture", conf, 3);	
	close(fd);
	p = path;
	while (ft_isprint(*p))
		p++;
	while (ft_isspace(*p))
		p++;
	if (*p)
		exit_error("When reading .cub file: bad texture path", conf, 3);	
}

int				validate_line(char **map, size_t y, t_conf *conf)
{
	int			closed;
	int			x;

	x = 0;
	closed = -1;
	while (ft_isspace(map[y][x]))
		x++;
	x--;
	while (map[y][++x])
		if (map[y][x] == '1')
			closed = 1;
		else if (closed > -1 && ft_strchr("NSWE20", map[y][x])
			&& !validate_updown(conf->map, x, y))
			closed = 0;
		else if (closed > 0 && ft_isspace(map[y][x]))
			closed = 0;	
		else
			return (0);
	return (closed);
}

int			validate_updown(t_map *map, size_t x, size_t y)
{
	char *hero;

	hero = ft_strchr("NSWE", map->matrix[y][x]);
	if (!map->matrix[y - 1][x] || ft_isspace(map->matrix[y - 1][x]))
			return (1);
	else if (y < map->y - 1 && (!map->matrix[y + 1][x] 
			|| ft_isspace(map->matrix[y + 1][x])))
		return (1);
	if (map->hero_x && hero)
		return (1);
	else if (hero)
	{
		map->hero_x = (double)x + 0.50;
		map->hero_y = (double)y + 0.50;
		map->hero_a = (*hero == 'N') * N + (*hero == 'S') * S
			+ (*hero == 'W') * W + (*hero == 'E') * E;
		map->matrix[y][x] = '0';
		map->hero_dx = cos(map->hero_a);
		map->hero_dy = sin(map->hero_a);
	}
	return (0);
}

void		handle_args(int ac, char **av)
{
	int		len;

	if (ac > 3 || ac < 2)
		exit_error("Wrong number of arguments", NULL, 1);
	else if (ac >= 2)
	{
		len = ft_strlen(av[1]);
		if (len < 4)
			exit_error("Invalid 1st argument", NULL, 1);
		else if (ft_strncmp(".cub", &av[1][len - 4], 5))
			exit_error("Invalid 1st argument", NULL, 1);
	}
	if (ac == 3 && ft_strncmp("--save", av[2], 7))
		exit_error("Invalid option: Try '--save'", NULL, 1);
}

int			validate_first_last_line(t_map *map)
{
	size_t	x;
	size_t	y;
	char	**matrix;

	x = -1;
	matrix = map->matrix;
	while (matrix[0][++x])
	{
		if (!ft_isspace(matrix[0][x])
				&& matrix[0][x] != '1')
			return (1);
	}
	x = -1;
	y = map->y - 1;
	while (matrix[y][++x])
	{
		if (!ft_isspace(matrix[y][x])
				&& matrix[y][x] != '1')
			return (1);
	}
	return (0);
}
