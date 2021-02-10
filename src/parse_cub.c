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
	
	config->line++;
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
		parse_rgb(line, config);
	else if (*line == 'N' || *line == 'W' ||
			 *line == 'S' || *line == 'E')
		parse_path(line, config);
	//else if (*line);
		//read_map(line);
	free(tmp);
}

void				parse_resolution(char *line, t_flags *config)
{
	if (config->res)
		exit_error("When reading .cub file: double R occuriance", config);
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

void				parse_rgb(char *line, t_flags *config)
{
	unsigned char	*rgb;
	int				i;

	if (config->ceiling && *line == 'C')
		exit_error("When reading .cub file: double C occuriance", 3);
	else if (config->floor && *line == 'F')
		exit_error("When reading .cub file: double F occuriance", 3);
	if (*line == 'C' && (config->ceiling = 1))
		rgb = config->values.ceiling;
	else if (*line == 'F' && (config->floor = 1))
		rgb = config->values.ceiling;
	if (!ft_isspace(*++line))
		exit_error("When reading .cub file: no space after F/C", 3);
	i = -1;
	while (++i < 3)
		rgb[i] = parse_color(&line, i);
	while (ft_isspace(*line))
		line++;
	if (*line)
		exit_error("When reading .cub file: bad symbol at the end of F/C field", 3);
}

unsigned char 		parse_color(char **line, int i)
{
	while (ft_isspace(**line))
		(*line)++;
	if ((i == 1 || i == 2) && **line != ',')
		exit_error("When reading .cub file: no ',' in color field", 3);
	else if (i == 1 || i == 2)
		(*line)++;
	while (ft_isspace(**line))
		(*line)++;
	if (!ft_isdigit(**line))
		exit_error("When reading .cub file: bad symbol at the color field", 3);
	if (!(ft_atoi(*line) & 0xFFFFFF00))
		return ((unsigned char)ft_skip_atoi(line));
	else
		exit_error("When reading .cub file: bad value for RGB color", 3);
	return (0);
}

void				parse_path(char *line, t_flags conf)
{
	char 			**path;

	if (*line == 'N' && *(line + 1) == 'O'
			&& (conf->no = 1))
		path = &(conf->values.no);	
	else if (*line == 'S' && *(line + 1) == 'O'
			&& (conf->so = 1))
		path = &(conf->values.so);	
	else if (*line == 'W' && *(line + 1) == 'E'
			&& (conf->we = 1))
		path = &(conf->values.we);
	else if (*line == 'S' && (conf->sprite = 1))
		path = &(conf->values.sprite);
	else 
		exit_error("When reading .cub file: bad setting", 3);
	line +=	path == &(conf->values.sprite) ? 1 : 2; 
	if (!(*path = ft_strtrim(line, "\r\t\n\v ")))
		exit_error("When allocating memory");
	validate_path(*path);
}
