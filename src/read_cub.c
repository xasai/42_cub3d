#include "cub3d.h"

void				read_cub(int ac, char **av)
{
	int				ret;
	int				fd;
	char			*line;
	t_conf			*conf;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		exit_error("When trying to open .cub file", conf, 2);
	config_init(&conf);
	while (conf->f.flag < 8 && (ret = get_next_line(fd, &line)) > 0)
	{
		parse_cub(line, conf);
		free(line);
	}
	if (ret < 0 || conf->f.flag != 8)
		exit_error("When reading .cub file", conf, 3);
	else
		read_map(fd, conf);
	if (ac == 3)
		conf->f.option = 1;
	close(fd);
}

void				read_map(int fd, t_conf *conf)
{
	int				ret;
	char			*line;
	t_maphead		maphead;

	maphead = (t_maphead){0};
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ret = append_maplst(line, ft_strlen(line), &maphead);
		if (ret)
			free(line); // skip all empty lines at start 
		if (ret == -1)
			exit_error("When allocating memory", conf, 4);
		else if (ret == -2)
			exit_error("Bad empty line in map", conf, 4);
	}
	if (ret < 0)
	{
		free(line);
		exit_error("Bad empty line in map", conf, 4);
	}
	conf->map = get_map(&maphead);
	for (size_t i=0;i < conf->map->y;i++)
		printf("%s\n", conf->map->matrix[i]);
}

int					append_maplst(char *line, size_t len, t_maphead *h)
{
	t_maplst		*new;
	
	if ((!h->head && ft_isempty_str(line)) || (*line &&
			h->head && !*(h->tail->line) && ft_isempty_str(line))) 
		return (1);
	if (h->head && *line && !*(h->tail->line))
		return (lst_clear(h->head, -2));
	new = ft_calloc(sizeof(*new), 1);
	if  (!new)
		return (lst_clear(h->head, -1));
	(*new) = (t_maplst){.next = NULL, .line = line, .len = len};
	if (ft_isempty_str(line))
		new->len = 0;
	if (!h->head)
	{
		h->tail = new;
		h->head = new;
	}
	else
	{
		h->tail->next = new;
		h->tail = new;
	}
	return (0);
}
