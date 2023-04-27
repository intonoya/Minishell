/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:19:00 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:19:03 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	*g_status;

void	add_double_quote(t_data *data, int i, int j, char *str)
{
	t_export	*tmp;

	tmp = data->_export;
	while (data->_export)
	{
		i = 0;
		j = 0;
		if (ft_strlen(data->_export->value) == 1)
			str = ft_empty_value();
		else
			str = norm_add_double_quote(data, i, j);
		free(data->_export->value);
		data->_export->value = ft_strdup(str);
		free(str);
		data->_export = data->_export->next;
	}
	data->_export = tmp;
}

void	ft_swap(t_export *_export)
{
	char	*tmp_key;
	char	*tmp_value;
	int		tmp_flag;

	tmp_key = _export->key;
	tmp_value = _export->value;
	tmp_flag = _export->flag;
	_export->key = _export->next->key;
	_export->value = _export->next->value;
	_export->flag = _export->next->flag;
	_export->next->key = tmp_key;
	_export->next->value = tmp_value;
	_export->next->flag = tmp_flag;
}

void	sort_export(t_data *data)
{
	t_export	*tmp;
	int			len;

	tmp = data->_export;
	while (data->_export->next)
	{
		len = size_str(data->_export->key, data->_export->next->key);
		if (ft_strncmp(data->_export->key, data->_export->next->key, len) > 0)
		{
			ft_swap(data->_export);
			data->_export = tmp;
			continue ;
		}
		data->_export = data->_export->next;
	}
	data->_export = tmp;
}

void	init_export(t_data *data, char **env, int i, char **ptr)
{
	t_export	*tmp;
	int			len;

	data->_export = malloc(sizeof(t_export));
	data->_export->next = 0;
	tmp = data->_export;
	while (env[++i])
	{
		ptr = ft_split(env[i], '=');
		len = size_str("OLDPWD", ptr[0]);
		data->_export->key = ft_strdup(ptr[0]);
		if (ft_strncmp("OLDPWD", ptr[0], len) == 0)
			data->_export->value = 0;
		else
			data->_export->value = ft_strdup(first_equal(env[i]));
		data->_export->flag = 0;
		free_array(&ptr);
		if (!env[i + 1])
			break ;
		data->_export->next = malloc(sizeof(t_export));
		data->_export = data->_export->next;
		data->_export->next = 0;
	}
	data->_export = tmp;
}

void	ft_export(t_data *data, char *str)
{
	t_export	*tmp;

	tmp = data->_export;
	while (str && *str && (*str == ' ' || *str == '\t'))
		str++;
	if (str && *str)
	{
		check_and_add_variables(data, str);
		return ;
	}
	while (data->_export)
	{
		if (data->_export->flag == 0)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(data->_export->key, 1);
			ft_putstr_fd(data->_export->value, 1);
			write(1, "\n", 1);
		}
		data->_export = data->_export->next;
	}
	data->_export = tmp;
	*g_status = 0;
}
