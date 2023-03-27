#include "minishell.h"

int	env(t_var **env_lst)
{
	int		i;
	char	**envp;

	i = -1;
	envp = env_lst_to_arr(*env_lst, 'e', 0);
	while (envp[++i] != 0)
	{
		ft_putstr_fd(envp[i], 1);
		ft_putchar_fd('\n', 1);
	}
	if (envp[i] == 0)
	{
		arr_free(envp);
		change_the_status(env_lst, 0);
		return (0);
	}
	else
	{
		arr_free(envp);
		change_the_status(env_lst, 127);
		return (2);
	}
}