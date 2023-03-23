#include "minishell.h"

void	lst_clear(t_var **lst, void (*del)(void *))
{
	t_var	*tmp;

	if (lst != 0 && *lst != 0)
	{
		while (*lst != 0)
		{
			tmp = (*lst)->next;
			lst_delone(*lst, del);
			*lst = tmp;
		}
	}
}

void	lst_clear_token(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	if (lst != 0 && *lst != 0)
	{
		while (*lst != 0)
		{
			tmp = (*lst)->next;
			lst_delone_token(*lst, del);
			*lst = tmp;
		}
	}
}