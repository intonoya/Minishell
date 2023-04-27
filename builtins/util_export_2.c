/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_export_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:20:35 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:20:38 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	norm_change_value_export(t_export *_export, char *str)
{
	char	*ptr;
	char	*str2;

	str2 = correct_heredoc_name(first_equal(str), 0, 0);
	ptr = strdup_for_export(_export->value);
	ptr = ft_strjoin(ptr, str2 + 1);
	ptr = ft_strjoin(ptr, "\"");
	free(_export->value);
	_export->value = ft_strdup(ptr);
	free(ptr);
	free(str2);
}

void	change_value_export(t_data *data, char *str)
{
	t_export	*tmp;
	char		**ptr;
	int			len;

	ptr = ft_split(str, '+');
	tmp = data->_export;
	while (data->_export)
	{
		len = size_str(ptr[0], data->_export->key);
		if (ft_strncmp(ptr[0], data->_export->key, len) == 0)
		{
			norm_change_value_export(data->_export, str);
			data->_export = tmp;
			free_array(&ptr);
			sort_export(data);
			return ;
		}
		data->_export = data->_export->next;
	}
	data->_export = tmp;
	free_array(&ptr);
	add_plus_and_equal_export(data, str);
}

int	n_check_key_export(t_data *data, char *str, char *str3, char **ptr)
{
	t_export	*tmp;
	int			len;
	char		*str2;

	tmp = data->_export;
	while (data->_export)
	{
		len = size_str(ptr[0], data->_export->key);
		if (ft_strncmp(ptr[0], data->_export->key, len) == 0)
		{
			str2 = correct_heredoc_name(first_equal(str), 0, 0);
			str3 = add_double_quotes_once_export \
			(str2, 0, 0, 0);
			if (str3)
				norm_check_key_export(data->_export, str3);
			free(str3);
			free(str2);
			data->_export = tmp;
			return (-1);
		}
		data->_export = data->_export->next;
	}
	data->_export = tmp;
	return (0);
}

int	check_key_export(t_data *data, char *str, char **ptr, char *str3)
{
	int		i;

	ptr = ft_split(str, '=');
	if (find_plus_and_equal(str) == 0)
	{
		change_value_export(data, str);
		free_array(&ptr);
		return (-1);
	}
	i = n_check_key_export(data, str, str3, ptr);
	free_array(&ptr);
	return (i);
}

void	add_variable_export(t_data *data, char *str)
{
	t_export	*tmp;
	char		**ptr;
	char		*str2;

	tmp = data->_export;
	if (check_key_export(data, str, 0, 0) == -1)
		return ;
	while (data->_export->next)
		data->_export = data->_export->next;
	data->_export->next = malloc(sizeof(t_export));
	data->_export = data->_export->next;
	data->_export->next = 0;
	ptr = ft_split(str, '=');
	data->_export->key = ft_strdup(ptr[0]);
	data->_export->flag = 0;
	str2 = correct_heredoc_name(first_equal(str), 0, 0);
	data->_export->value = add_double_quotes_once_export(str2, 0, 0, 0);
	free(str2);
	data->_export = tmp;
	free_array(&ptr);
	sort_export(data);
}
