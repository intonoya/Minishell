/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:20:05 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:20:07 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_plus_and_equal(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (0);
	}
	return (-1);
}

void	add_plus_and_equal_env(t_data *data, char *str)
{
	t_env	*tmp;
	char	**ptr;
	char	*str2;

	tmp = data->_env;
	while (data->_env->next)
		data->_env = data->_env->next;
	data->_env->next = malloc(sizeof(t_env));
	data->_env = data->_env->next;
	data->_env->next = 0;
	str2 = 0;
	ptr = ft_split(str, '+');
	data->_env->key = ft_strdup(ptr[0]);
	str2 = correct_heredoc_name(first_equal(str), 0, 0);
	data->_env->value = ft_strdup(str2);
	data->_env->flag = 0;
	data->_env = tmp;
	free_array(&ptr);
	free(str2);
}

void	change_value_env(t_data *data, char *str)
{
	t_env	*tmp;
	char	**ptr;
	int		len;

	ptr = ft_split(str, '+');
	tmp = data->_env;
	while (data->_env)
	{
		len = size_str(ptr[0], data->_env->key);
		if (ft_strncmp(ptr[0], data->_env->key, len) == 0)
		{
			data->_env->value = ft_strjoin \
			(data->_env->value, first_equal(str) + 1);
			data->_env = tmp;
			free_array(&ptr);
			return ;
		}
		data->_env = data->_env->next;
	}
	data->_env = tmp;
	free_array(&ptr);
	add_plus_and_equal_env(data, str);
}

int	n_check_key_env(t_data *data, char **ptr, char *str, char *str2)
{
	t_env	*tmp;
	int		len;

	tmp = data->_env;
	while (data->_env)
	{
		len = size_str(data->_env->key, ptr[0]);
		if (ft_strncmp(ptr[0], data->_env->key, len) == 0)
		{
			free(data->_env->value);
			str2 = correct_heredoc_name(first_equal(str), 0, 0);
			data->_env->value = ft_strdup(str2);
			free(str2);
			data->_env = tmp;
			return (-1);
		}
		data->_env = data->_env->next;
	}
	data->_env = tmp;
	return (0);
}

int	check_key_env(t_data *data, char *str, char *str2, char **ptr)
{
	int		i;

	if (find_plus_and_equal(str) == 0)
	{
		change_value_env(data, str);
		return (-1);
	}
	ptr = ft_split(str, '=');
	i = n_check_key_env(data, ptr, str, str2);
	free_array(&ptr);
	return (i);
}
