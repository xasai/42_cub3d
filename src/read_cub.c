#include "cub3d.h"

void				read_cub(int ac, char **av)
{
	int				ret;
	int				fd;
	char			*line;
	t_flags 		*config;
	
	fd = open(av[1], O_RDONLY);
	if (fd < 3)
		exit_error("When trying to open file", 1);
	config_init(&config);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		parse_cub(line, config);
	}
	if (ret < 0)
		exit_error("When read file", 2);
	if (ac == 3)
		return ; // --save config option
}

void 				parse_cub(char *line, t_flags *config) 
{
	char			*tmp;

	tmp = line;
	while (ft_isspace(*line))
		line++;
	if (!*line)
	{
		free(line);
		return ;
	}
	if (*line == 'R')
		parse_resolution(++line, config);
	else if (*line == 'C' || *line == 'F')
		parse_color(line, config);
	//else if (ft_isalpha(*line))
		//parse_path(line, config);
	//else if (*line);
		//read_map(line);
	free(tmp);
}

void				parse_resolution(char *line, t_flags *config)
{
	if (config->res)
		exit_error("When reading .cub file: double R occuriance", 3);
	config->res = 1;
	if (!ft_isspace(*line))
		exit_error("When reading .cub file: wrong R field", 3);
	config->values.res_x = ft_skip_atoi(&line);
	if (!ft_isspace(*line))
		exit_error("When reading .cub file: wrong R field", 3);
	config->values.res_y = ft_skip_atoi(&line);
	while (ft_isspace(*line))
		line++;
	if (*line)
		exit_error("When reading .cub file: bad symbol at the end of R field", 3);
}

void				parse_color(char *line, t_flags *config)
{
	unsigned char	*rgb;
	int				i;

	if (config->ceiling && *line == 'C')
		exit_error("When reading .cub file: double C occuriance", 3);
	else if (line == 'F' && config->floor)
		exit_error("When reading .cub file: double F occuriance", 3);
	if (*line == 'C')
		config->ceiling = 1;
	else
		config->floor = 1;
	if (!ft_isspace(*line))
		line++;
// Heres gonna be cycle for array of unsigned chars whereas i should put 3 nums 	
	
}
