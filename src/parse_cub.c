#include "cub3d.h"

void 				parse_cub(char *line, t_conf *conf) 
{
	conf->line_num++;
	while (ft_isspace(*line))
		line++;
	if (!*line)
		return ;
	if (*line == 'R')
		parse_resolution(++line, conf);
	else if (*line == 'C' || *line == 'F')
		parse_rgb(line, conf);
	else if (*line == 'N' || *line == 'W' ||
			 *line == 'S' || *line == 'E')
		parse_path(line, conf);
}

void				parse_resolution(char *line, t_conf *conf)
{
	if (conf->f.res)
		exit_error("double R occuriance", conf, 3);
	conf->f.res = 1;
	if (!ft_isspace(*line))
		exit_error("Missing space after R", conf, 3);
	conf->res_x = ft_skip_atoi(&line);
	if (!ft_isspace(*line))
		exit_error("Bad R field", conf, 3);
	conf->res_y = ft_skip_atoi(&line);
	while (ft_isspace(*line))
		line++;
	if (*line)
		exit_error("bad symbol at the end of R field", conf, 3);
	conf->f.flag++;
}

void				parse_rgb(char *line, t_conf *conf)
{
	unsigned char	*rgb;
	int				i;

	if (conf->f.ceiling && *line == 'C')
		exit_error("double C occuriance", conf, 3);
	else if (conf->f.floor && *line == 'F')
		exit_error("double F occuriance", conf, 3);
	if (*line == 'C' && (conf->f.ceiling = 1))
		rgb = conf->ceiling;
	else if (*line == 'F' && (conf->f.floor = 1))
		rgb = conf->floor;
	if (!ft_isspace(*++line))
		exit_error("no space after specificator", conf, 3);
	i = -1;
	while (++i < 3)
		rgb[i] = parse_color(&line, conf, i);
	while (ft_isspace(*line))
		line++;
	if (*line)
		exit_error("bad symbol at the end of field", conf, 3);
	conf->f.flag++;
}

char		 		parse_color(char **line, t_conf *conf, int i)
{
	while (ft_isspace(**line))
		(*line)++;
	if ((i == 1 || i == 2) && **line != ',')
		exit_error("Syntax 255,255,255", conf, 3);
	else if (i == 1 || i == 2)
		(*line)++;
	while (ft_isspace(**line))
		(*line)++;
	if (!ft_isdigit(**line))
		exit_error("bad field", conf, 3);
	if (!(ft_atoi(*line) & 0xFFFFFF00))
		return ((unsigned char)ft_skip_atoi(line));
	else
		exit_error("bad value for RGB color", conf, 3);
	return (0x0);	
}

void				parse_path(char *line, t_conf *conf)
{
	char 			**path;
	int				test_fd;	

	path = NULL;
	if (*line == 'N' && *(line + 1) == 'O' && (conf->f.no = 1))
		path = &(conf->no);	
	else if (*line == 'S' && *(line + 1) == 'O'	&& (conf->f.so = 1))
		path = &(conf->so);	
	else if (*line == 'W' && *(line + 1) == 'E'	&& (conf->f.we = 1))
		path = &(conf->we);
	else if (*line == 'S' && (conf->f.sprite = 1))
		path = &(conf->sprite);
	else if (*line == 'E' && *(line + 1) == 'A'	&& (conf->f.ea = 1))
		path = &(conf->ea);
	else 
		exit_error("bad setting", conf, 3);
	line +=	path == &(conf->sprite) ? 1 : 2; 
	if (!(*path = ft_strtrim(line, "\r\t\n\v ")))
		exit_error("When allocating memory", conf, 3);
	validate_path(*path, conf);
	if ((test_fd = open(*path, O_RDONLY)) < 0)
		exit_error("error occured while opening texture file", conf, 3);
	close(test_fd);
	conf->f.flag++;
}
