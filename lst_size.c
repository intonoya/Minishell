#include "minishell.h"

int	lst_size(t_var *lst)
{
	int	count;

	count = 0;
	while (lst != 0)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

int	lst_size_token(t_token *lst)
{
	int	count;

	count = 0;
	while (lst != 0)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}