#include "cub3d.h"

void			get_map(t_maphead *maphead, t_conf *conf)
{
	t_map		*map;

	map = conf->map;
	remove_empty_tails(maphead);
	if (get_sizes_map(maphead->head, &map->x, &map->y))
		exit_error("Bad map", conf, 4);
	map->matrix = ft_calloc(sizeof(char **), map->y);
	if (!map->matrix)
		exit_error("When allocating memory", conf, 4);
	if (map_matrix(map->matrix, maphead->head, map->x, map->y))
		exit_error("Bad map", conf, 4);
	fill_map(conf);
}

void			fill_map(t_conf *conf)
{
	char		**matrix;
	size_t		y;

	matrix = conf->map->matrix;
	if (validate_first_last_line(conf->map))
		exit_error("Map is not closed on top or bottom", conf, 4);
	y = 0;
	while (++y < conf->map->y - 1)
		if (!validate_line(matrix, y, conf))
		{
			printf("%lu\n",y);
			exit_error("Bad map", conf, 4);
		}
	if (!conf->map->hero_x)
		exit_error("Bad map: No hero found [N|W|S|E]", conf, 4);
}

int				get_sizes_map(t_maplst *lst, size_t *x, size_t *y)
{
	*y = 0;
	*x = 0;

	while (lst)
	{
		*y += 1;
		if (lst->len > *x)
			*x = lst->len;
		lst = lst->next;
	}
	if (*x < 3 || *y < 3)
		return (1);
	return (0);
}

int				map_matrix(char **matrix, t_maplst *head, size_t x, size_t y)
{
	size_t		i;
	
	i = -1;
	if (!matrix)
		return (matrix_clear(matrix, 0));
	while (++i < y)
	{
		matrix[i] = ft_calloc(sizeof(char), x + 1);
		if (!matrix[i])
			return (matrix_clear(matrix, i));
		ft_strlcpy(matrix[i], head->line, x + 1);
		head = head->next;
	}
	return (0);
}

void			remove_empty_tails(t_maphead *mhead)
{
	t_maplst	*last;
	t_maplst	*prev;

	
	while (!mhead->tail->len)
	{
		last = mhead->tail;
		prev = mhead->head;
		while (prev->next != last)
			prev = prev->next;
		free(last->line);
		free(last);
		mhead->tail = prev;
	}
}
