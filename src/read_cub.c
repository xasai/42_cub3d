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
	while (conf->f.flag != 8 && (ret = get_next_line(fd, &line)) > 0)
	{
		parse_cub(line, conf);
		free(line);
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
	t_list			*lst_head;
	
	was_empty = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!was_empty && ft_isempty_str(line) &&
				(was_empty = 1))
			append_lst(line, &lst_head, conf);
		else if (!ft_isempty_str(line))
		{
			conf->map->x = ret > conf->map->x ? ret : conf->map->x;
			append_lst(line, &lst_head, conf);
			was_empty = 0;
		}
		else
			free(line);
	}
	if (ret < 0)
		exit_error("When allocating memory", conf, 4);
	make_map(conf->map, &lst_head, conf); 
}

void				make_map(t_map *map_t, t_list **lst_head, t_conf *conf)
{
	t_list			*cur;
	int				i;	
	char			**map;

	cur = ft_lstlast(*lst_head);
	i = ft_strlen(cur->content);
	if (!ft_isempty_str(cur->content))
		map_t->x = map_t->x > i ? map_t->x : i;
	if (!(map = malloc(sizeof(*map) * map_t->y)))
		exit_error("When allocating memory", conf, 4);
	i = -1;
	while (++i < map_t->y)
	{
		cur = *lst_head;
		if (!(map[i] = ft_calloc(sizeof(char), map_t->x)))
			exit_error("When allocating memory", conf, 4);
		ft_memset(map[i], ' ', map_t->x - 1);
		ft_memcpy(map[i], cur->content, ft_strlen(cur->content));
		*lst_head = (*lst_head)->next;
		free(cur->content);
		free(cur);
	}
	map_t->map = map;
}

void				append_lst(char *line, t_list **lst_head, t_conf *conf)
{
	t_list			*lst_new;
	
	if (!(lst_new = ft_lstnew(line)))
		exit_error("When allocating memory", conf, 4);
	(ft_lstlast(*lst_head))->next = lst_new;
	conf->map->y++;
}
