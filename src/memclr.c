#include "cub3d.h"

int				lst_clear(t_maplst *head, int ret)
{
	t_maplst 	*next;

	while (head)
	{
		next = head->next;
		free(head->line);
		free(head);
		head = next;
	}
	return (ret);
}

int				matrix_clear(char **matrix, size_t i)
{
	size_t		k;
	
	k = 0;
	while (k < i)
		free(matrix[k++]);
	free(matrix);
	return (1);
}
