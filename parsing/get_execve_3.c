/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_execve_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:07:53 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:08:00 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_node(t_data *data)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = data->_env;
	while (data->_env)
	{
		data->_env = data->_env->next;
		count++;
	}
	data->_env = tmp;
	return (count);
}

char	**get_correct_env(t_data *data)
{
	t_env	*tmp;
	int		i;
	char	**correct_env;

	tmp = data->_env;
	correct_env = malloc(sizeof(char *) * (count_node(data) + 1));
	i = 0;
	while (data->_env)
	{
		if (data->_env->flag == 0)
		{
			correct_env[i] = ft_strdup(data->_env->key);
			correct_env[i] = ft_strjoin(correct_env[i], data->_env->value);
			i++;
		}
		data->_env = data->_env->next;
	}
	correct_env[i] = 0;
	data->_env = tmp;
	return (correct_env);
}
