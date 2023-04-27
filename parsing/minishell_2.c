/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:08:32 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:08:36 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*g_status;

void	get_exit(t_data *data)
{
	int	error_code;

	error_code = *data->error_code;
	write(1, "exit\n", 5);
	get_and_set_attr(1);
	free_all(data, 0);
	exit(error_code);
}

int	a(void)
{
	return (0);
}

t_data	init_lists(int argc, char **argv, char **env, t_data *data)
{
	init_env(data, env, 0, -1);
	init_export(data, env, -1, 0);
	sort_export(data);
	add_double_quote(data, 0, 0, 0);
	rl_event_hook = a;
	(void)(argc+argv);
	return (*data);
}

void	norm_change_shlvl(t_data *data, int shlvl, char *new_shlvl)
{
	shlvl = ft_atoi(data->_env->value + 1);
	shlvl++;
	if (shlvl > 1000)
	{
		ft_putstr_fd("❌ minishell: warning: shell level (", STDOUT_FILENO);
		ft_putstr_fd(ft_itoa(shlvl), STDOUT_FILENO);
		ft_putstr_fd(") too high, resetting to 1\n", STDOUT_FILENO);
		shlvl = 1;
	}
	else if (shlvl == 1000)
		shlvl = 0;
	free(data->_env->value);
	data->_env->value = 0;
	new_shlvl = ft_itoa(shlvl);
	if (shlvl == 0)
		data->_env->value = 0;
	else
	{
		data->_env->value = ft_strdup("=");
		data->_env->value = ft_strjoin(data->_env->value, new_shlvl);
	}
	free(new_shlvl);
	new_shlvl = 0;
}

void	change_shlvl(t_data *data)
{
	t_env	*tmp;
	int		len;
	char	*str;
	char	*new_shlvl;
	char	*check;

	new_shlvl = 0;
	check = 0;
	str = 0;
	tmp = data->_env;
	len = 0;
	while (data->_env)
	{
		len = size_str(data->_env->key, "SHLVL");
		if (ft_strncmp(data->_env->key, "SHLVL", len) == 0)
		{
			norm_change_shlvl(data, 0, 0);
			break ;
		}
		data->_env = data->_env->next;
	}
	data->_env = tmp;
	change_shlvl_in_export(data, check, str, new_shlvl);
}
