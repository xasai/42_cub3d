#include "cub3d.h"

void				read_cub(int ac, char **av)
{
	int				ret;
	int				fd;
	char			*line;
	t_conf			*conf;

	conf_init(&conf);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		exit_error("When trying to open file", conf, 3);
	while ((ret = get_next_line(fd, &line)) >= 0)
	{
		parse_cub(line, conf);
		free(line);
		if (conf->f.flag == 8)
			break ;
	}
	if (ret < 0)
		exit_error("When reading .cub file", conf, 3);
	else if (conf->f.flag == 8)
		read_map(fd, conf);
	else
		exit_error("Invalid .cub file", conf, 3);
	if (ac == 3)
		conf->f.option = 1;
	close(fd);
}

void				read_map(int fd, t_conf *conf)
{
	int				ret;
	int				was_empty;
	char			*line;
	t_list			*lst_new;
	t_list			*lst_head;
	
	was_empty = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		lst_new = NULL;
		if (!was_empty && ft_isempty_str(line) && (was_empty = 1)
			&& !(lst_new = ft_lstnew(line)))
			exit_error("When allocating memory", conf, 4);
		else if (!ft_isempty_str(line))
		{
			if (!(lst_new = ft_lstnew(line)))
				exit_error("When allocating memory", conf, 4);
			was_empty = 0;
		}
		if (lst_new && ++(conf->map->map_y))
			ft_lstadd_back(&lst_head, lst_new);
		else
			free(line);
	}
}

