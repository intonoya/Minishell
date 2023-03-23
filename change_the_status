#include "minishell.h"

void	change_the_status(t_var **env_lst, int status)
{
	t_var	*tmp;

	tmp = *env_lst;
	while (tmp->meaning != '?')
		tmp = tmp->next;
	tmp->status = status;
	if (tmp->value != 0)
		free(tmp->value);
	tmp->value = ft_itoa(tmp->status);
}