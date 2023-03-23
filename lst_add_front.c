#include "minishell.h"

void	lst_add_front(t_var **lst, t_var *new_elem)
{
	if (lst && new_elem)
	{
		new_elem->next = *lst;
		*lst = new_elem;
	}
}