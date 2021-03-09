#include "cub3d.h"

t_map			*get_map(t_maphead *maphead)
{
	t_map		*map;

	map = ft_calloc(sizeof(*map), 1);
	if (!map)
		return (NULL);
	if (get_sizes_map(maphead->head, &map->x, &map->y))
	{
		free(map);
		return (NULL);
	}
	map->matrix = ft_calloc(sizeof(char *), map->y);
	if (map_matrix(map->matrix, maphead->head, map->x, map->y))
	{
		free(map);
		return (NULL);
	}				
	return (map);
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

