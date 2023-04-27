/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:24:32 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:24:35 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*correct_value(char *str)
{
	char	*ptr;
	int		i;
	int		j;

	ptr = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!ptr)
		return (0);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (!((str[i] >= 'a' && str[i] <= 'z') || \
					(str[i] >= 'A' && str[i] <= 'Z') || str[i] == '$'))
		{
			ptr[j] = str[i];
			i++;
			j++;
		}
		break ;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*get_end_value(char *str)
{
	char	*ptr;
	int		i;
	int		j;

	ptr = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!ptr)
		return (0);
	i = 0;
	j = 0;
	while (str[i] && (str[i] == '\'' || str[i] == '\"'))
		i++;
	while (str[i] && (str[i] == '$' || (str[i] >= 'a' && str[i] <= 'z') \
		|| (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' \
		&& str[i] <= '9')))
		i++;
	while (str[i])
	{
		ptr[j] = str[i];
		i++;
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*get_value(t_data *data, char *check, char *clear_check, int i)
{
	t_env	*tmp;
	char	*correct_value_name;
	char	*clear;

	tmp = data->_env;
	clear = clear_str(check);
	clear++;
	while (data->_env)
	{
		i = size_str(data->_env->key, clear);
		if (data->_env->flag == 0 && data->_env->key \
				&& ft_strncmp(data->_env->key, clear, i - 1) == 0)
		{
			correct_value_name = correct_value(check);
			check = ft_strdup(data->_env->value);
			correct_value_name = ft_strjoin(correct_value_name, check);
			correct_value_name = ft_strjoin(correct_value_name, \
					get_end_value(clear_check));
			data->_env = tmp;
			return (correct_value_name);
		}
		data->_env = data->_env->next;
	}
	data->_env = tmp;
	return (check);
}
