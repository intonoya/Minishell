/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:19:42 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:19:49 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	*g_status;

char	*find_home(t_data *data)
{
	t_env	*tmp;
	char	*home;
	int		len;

	tmp = data->_env;
	home = 0;
	while (data->_env)
	{
		len = size_str("HOME", data->_env->key);
		if (ft_strncmp("HOME", data->_env->key, len) == 0 && \
		data->_env->flag == 0)
		{
			home = ft_strdup(data->_env->value + 1);
			break ;
		}
		data->_env = data->_env->next;
	}
	data->_env = tmp;
	return (home);
}

char	*find_pwd(t_data *data)
{
	t_env	*tmp;
	char	*pwd;
	int		len;

	tmp = data->_env;
	pwd = 0;
	while (data->_env)
	{
		len = size_str("PWD", data->_env->key);
		if (ft_strncmp("PWD", data->_env->key, len) == 0)
		{
			pwd = ft_strdup(data->_env->value);
			break ;
		}
		data->_env = data->_env->next;
	}
	data->_env = tmp;
	return (pwd);
}

void	add_oldpwd(t_data *data, char *pwd)
{
	t_env	*tmp;

	tmp = data->_env;
	while (data->_env->next)
		data->_env = data->_env->next;
	data->_env->next = malloc(sizeof(t_env));
	data->_env = data->_env->next;
	data->_env->next = 0;
	data->_env->key = ft_strdup("OLDPWD");
	data->_env->value = ft_strdup(pwd);
	data->_env->flag = 0;
	data->_env = tmp;
}

void	change_oldpwd_env(t_data *data)
{
	t_env	*tmp;
	int		len;
	char	*pwd;

	tmp = data->_env;
	pwd = find_pwd(data);
	while (data->_env)
	{
		len = size_str("OLDPWD", data->_env->key);
		if (ft_strncmp("OLDPWD", data->_env->key, len) == 0)
		{
			free(data->_env->value);
			data->_env->value = 0;
			data->_env->value = ft_strdup(pwd);
			data->_env = tmp;
			free(pwd);
			return ;
		}
		data->_env = data->_env->next;
	}
	data->_env = tmp;
	add_oldpwd(data, pwd);
	free(pwd);
}

void	change_pwd_env(t_data *data)
{
	t_env	*tmp;
	int		len;
	char	*buff;

	tmp = data->_env;
	buff = 0;
	while (data->_env)
	{
		len = size_str("PWD", data->_env->key);
		if (ft_strncmp("PWD", data->_env->key, len) == 0)
		{
			free(data->_env->value);
			data->_env->value = 0;
			buff = getcwd(buff, 1024);
			data->_env->value = ft_strjoin(data->_env->value, "=");
			data->_env->value = ft_strjoin(data->_env->value, buff);
			data->_env = tmp;
			free(buff);
			return ;
		}
		data->_env = data->_env->next;
	}
	data->_env = tmp;
}
