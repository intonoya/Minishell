#include "minishell.h"

void	arr_free(char **arr)
{
	int	i;

	i = -1;
	if (arr != 0)
	{
		while (arr[++i] != 0)
			free(arr[i]);
		free(arr);
	}
}