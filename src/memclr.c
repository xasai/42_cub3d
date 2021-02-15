#include "cub3d.h"

void	lst_clear(t_list *lst)
{
	t_list *next;

	if (!lst)
		return ; 
	while (lst)
	{
		free(lst->content);
		next = lst->next;
		free(lst);
		lst = next;
	}
}
