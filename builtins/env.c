/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:18:40 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:18:42 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	*g_status;

char	*first_equal(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != '=')
		;
	if (str[i])
		return (&str[i]);
	return (NULL);
}

void	init_env(t_data *data, char **env, char **ptr, int i)
{
	t_env	*tmp;
	int		len;

	data->_env = malloc(sizeof(t_env));
	data->_env->next = 0;
	tmp = data->_env;
	while (env[++i])
	{
		ptr = ft_split(env[i], '=');
		len = size_str("OLDPWD", ptr[0]);
		if (ft_strncmp("OLDPWD", ptr[0], len) == 0)
			data->_env->value = 0;
		else
			data->_env->value = ft_strdup(first_equal(env[i]));
		data->_env->flag = 0;
		data->_env->key = ft_strdup(ptr[0]);
		free_array(&ptr);
		if (!env[i + 1])
			break ;
		data->_env->next = malloc(sizeof(t_env));
		data->_env = data->_env->next;
		data->_env->next = 0;
	}
	data->_env = tmp;
}

void	ft_env(t_data *data)
{
	t_env	*tmp;

	tmp = data->_env;
	while (data->_env)
	{
		if (data->_env->flag == 0 && data->_env->value)
		{
			ft_putstr_fd(data->_env->key, 1);
			ft_putstr_fd(data->_env->value, 1);
			write(1, "\n", 1);
		}
		data->_env = data->_env->next;
	}
	data->_env = tmp;
	*g_status = 0;
}

int	check_add_env(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (0);
	}
	return (-1);
}

void	add_variable_env(t_data *data, char *str)
{
	t_env	*tmp;
	char	**ptr;
	char	*str2;

	if (check_key_env(data, str, 0, 0) == -1)
		return ;
	str2 = 0;
	tmp = data->_env;
	while (data->_env->next)
		data->_env = data->_env->next;
	data->_env->next = malloc(sizeof(t_env));
	data->_env = data->_env->next;
	data->_env->next = 0;
	ptr = ft_split(str, '=');
	data->_env->key = ft_strdup(ptr[0]);
	str2 = correct_heredoc_name(first_equal(str), 0, 0);
	data->_env->value = ft_strdup(str2);
	data->_env->flag = 0;
	data->_env = tmp;
	free_array(&ptr);
	free(str2);
}
