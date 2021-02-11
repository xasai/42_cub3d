#include "cub3d.h"

void 				parse_cub(char *line, t_flags *config) 
{
	config->line_num++;
	config->alloced_line = line;
	while (ft_isspace(*line))
		line++;
	if (!*line)
		return ;
	if (*line == 'R')
		parse_resolution(++line, config);
	else if (*line == 'C' || *line == 'F')
		parse_rgb(line, config);
	else if (*line == 'N' || *line == 'W' ||
			 *line == 'S' || *line == 'E')
		parse_path(line, config);
	//else
		//read_map(line, config);
}

void				parse_resolution(char *line, t_flags *config)
{
	if (config->res)
		exit_error("double R occuriance", config, 3);
	config->res = 1;
	if (!ft_isspace(*line))
		exit_error("wrong R field", config, 3);
	config->values.res_x = ft_skip_atoi(&line);
	if (!ft_isspace(*line))
		exit_error("wrong R field", config, 3);
	config->values.res_y = ft_skip_atoi(&line);
	while (ft_isspace(*line))
		line++;
	if (*line)
		exit_error("bad symbol at the end of R field", config, 3);
}

void				parse_rgb(char *line, t_flags *config)
{
	unsigned char	*rgb;
	int				i;

	if (config->ceiling && *line == 'C')
		exit_error("double C occuriance", config, 3);
	else if (config->floor && *line == 'F')
		exit_error("double F occuriance", config, 3);
	if (*line == 'C' && (config->ceiling = 1))
		rgb = config->values.ceiling;
	else if (*line == 'F' && (config->floor = 1))
		rgb = config->values.floor;
	if (!ft_isspace(*++line))
		exit_error("no space after specificator", config, 3);
	i = -1;
	while (++i < 3)
		rgb[i] = parse_color(&line, config, i);
	while (ft_isspace(*line))
		line++;
	if (*line)
		exit_error("bad symbol at the end of field", config, 3);
}

unsigned char 		parse_color(char **line, t_flags *config, int i)
{
	while (ft_isspace(**line))
		(*line)++;
	if ((i == 1 || i == 2) && **line != ',')
		exit_error("syntax 255,255,255", config, 3);
	else if (i == 1 || i == 2)
		(*line)++;
	while (ft_isspace(**line))
		(*line)++;
	if (!ft_isdigit(**line))
		exit_error("bad field", config, 3);
	if (!(ft_atoi(*line) & 0xFFFFFF00))
		return ((unsigned char)ft_skip_atoi(line));
	else
		exit_error("bad value for RGB color", config, 3);
	return (0);
}

void				parse_path(char *line, t_flags *config)
{
	char 			**path;
	int				test_fd;	

	path = NULL;
	if (*line == 'N' && *(line + 1) == 'O' && (config->no = 1))
		path = &(config->values.no);	
	else if (*line == 'S' && *(line + 1) == 'O'	&& (config->so = 1))
		path = &(config->values.so);	
	else if (*line == 'W' && *(line + 1) == 'E'	&& (config->we = 1))
		path = &(config->values.we);
	else if (*line == 'S' && (config->sprite = 1))
		path = &(config->values.sprite);
	else if (*line == 'E' && *(line + 1) == 'A'	&& (config->ea = 1))
		path = &(config->values.ea);
	else 
		exit_error("bad setting", config, 3);
	line +=	path == &(config->values.sprite) ? 1 : 2; 
	if (!(*path = ft_strtrim(line, "\r\t\n\v ")))
		exit_error("When allocating memory", config, 3);
	validate_path(*path, config);
	if ((test_fd = open(*path, O_RDONLY)) < 0)
		exit_error("error occured while opening texture file", config, 3);
	close(test_fd);
}
