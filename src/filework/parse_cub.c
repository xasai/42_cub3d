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
	if (conf->flag & 0x01)
		exit_error("double R occuriance", conf, 3);
	if (!ft_isspace(*line))
		exit_error("Missing space after R", conf, 3);
	conf->res_x = (uint16_t)ft_skip_atoi(&line);
	if (!ft_isspace(*line))
		exit_error("Bad R field", conf, 3);
	conf->res_y = (uint16_t)ft_skip_atoi(&line);
	while (ft_isspace(*line))
		line++;
	if (*line)
		exit_error("bad symbol at the end of R field", conf, 3);
	conf->flag |= 0x01;
}

void				parse_rgb(char *line, t_conf *conf)
{
	char 			*rgb;
	int				i;

	i = 3;
	rgb = NULL;
	if (conf->flag & 0x02 && *line == 'C')
		exit_error("double C occuriance", conf, 3);
	else if (conf->flag & 0x04 && *line == 'F')
		exit_error("double F occuriance", conf, 3);
	else if (*line == 'C')
	{
		rgb = (char *)&conf->ceiling;
		conf->flag |= 0x02;
	}
	else if (*line == 'F')
	{
		rgb = (char *)&conf->floor;
		conf->flag |= 0x04;
	}
	if (!ft_isspace(*++line))
		exit_error("no space after specificator", conf, 3);
	while (--i >= 0)
		rgb[i] = parse_color(&line, conf, i);
	while (ft_isspace(*line))
		line++;
	if (*line)
		exit_error("bad symbol at the end of color field", conf, 3);
}

char		 		parse_color(char **line, t_conf *conf, int i)
{
	while (ft_isspace(**line))
		(*line)++;
	if ((i == 0 || i == 1) && **line != ',')
		exit_error("Syntax: RGB: 255,127,0", conf, 3);
	else if (i == 0 || i == 1)
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

	path = NULL;
	if (*line == 'N' && *(line + 1) == 'O')
		path = &(conf->no);	
	else if (*line == 'S' && *(line + 1) == 'O')
		path = &(conf->so);	
	else if (*line == 'W' && *(line + 1) == 'E')
		path = &(conf->we);
	else if (*line == 'S')
		path = &(conf->sprite);
	else if (*line == 'E' && *(line + 1) == 'A')
		path = &(conf->ea);
	else 
		exit_error("Bad texture", conf, 3);
	if (path != &(conf->sprite))
		line++;
	line++;
	*path = ft_strtrim(line, "\t\n\v ");
	if (!path)
		exit_error("When allocating memory", conf, 3);
	validate_path(*path, conf);
	set_texture_flag(*path, conf);
}
 
void				set_texture_flag(char *path, t_conf *conf)
{
	if (path == conf->no && !(conf->flag & 0x80))
		conf->flag |= 0x80;
	else if (path == conf->so && !(conf->flag & 0x30))
		conf->flag |= 0x40;
	else if (path == conf->we && !(conf->flag & 0x20))
		conf->flag |= 0x20;
	else if (path == conf->ea && !(conf->flag & 0x10))
		conf->flag |= 0x10;
	else if (path == conf->sprite && !(conf->flag & 0x08))
		conf->flag |= 0x08;
	else 
		exit_error("Double texture occuriance", conf, 3);
}
