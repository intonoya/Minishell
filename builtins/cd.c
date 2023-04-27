/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:18:24 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:18:28 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	*g_status;

void	change_oldpwd_export(t_data *data)
{
	t_export	*tmp;
	int			len;
	char		*pwd;

	tmp = data->_export;
	pwd = find_pwd_export(data);
	while (data->_export)
	{
		len = size_str("OLDPWD", data->_export->key);
		if (ft_strncmp("OLDPWD", data->_export->key, len) == 0)
		{
			free(data->_export->value);
			data->_export->value = ft_strdup(pwd);
			break ;
		}
		data->_export = data->_export->next;
	}
	data->_export = tmp;
	free(pwd);
}

void	change_pwd_export(t_data *data, char *buff, char *ptr, int len)
{
	t_export	*tmp;

	tmp = data->_export;
	while (data->_export)
	{
		len = size_str("PWD", data->_export->key);
		if (ft_strncmp("PWD", data->_export->key, len) == 0)
		{
			free(data->_export->value);
			data->_export->value = 0;
			buff = getcwd(buff, 1024);
			data->_export->value = ft_strjoin(data->_export->value, "=");
			data->_export->value = ft_strjoin(data->_export->value, buff);
			ptr = add_double_quotes_once_export(data->_export->value, 0, 0, 0);
			free(data->_export->value);
			data->_export->value = ft_strdup(ptr);
			free(buff);
			free(ptr);
			break ;
		}
		data->_export = data->_export->next;
	}
	data->_export = tmp;
}

void	chang_pwd_and_oldpwd(t_data *data)
{
	change_oldpwd_env(data);
	change_pwd_env(data);
	change_oldpwd_export(data);
	change_pwd_export(data, 0, 0, 0);
}

void	n_ft_cd(char **ptr, char *str2, char *str)
{	
	ptr = ft_split(str, ' ');
	str2 = correct_heredoc_name(ptr[0], 0, 0);
	if (chdir(str2) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str2, 2);
		perror(" ");
		*g_status = 1;
		free_array(&ptr);
		free(str2);
		return ;
	}
	free_array(&ptr);
	free(str2);
	*g_status = 0;
}

void	ft_cd(t_data *data, char *str)
{
	char	*home;

	home = find_home(data);
	if (!str)
	{
		if (chdir(home) < 0)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			*g_status = 1;
		}
	}
	else
		n_ft_cd(0, 0, str);
	free(home);
	chang_pwd_and_oldpwd(data);
}
