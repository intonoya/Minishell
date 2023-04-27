/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_get_value_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:14:18 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:14:22 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*norm_change_dollar(t_data *data, char *delim)
{
	char	*ptr;
	int		len;

	ptr = 0;
	len = 0;
	if (delim && !*delim)
	{
		ptr = ft_strdup("$");
		return (ptr);
	}
	len = size_str(delim, "?");
	if (ft_strncmp(delim, "?", 1) == 0)
	{
		ptr = ft_itoa(*data->error_code);
		return (ptr);
	}
	return (ptr);
}

char	*change_dollar(t_data *data, char *delim, int len, char *ptr)
{
	t_env	*tmp;

	tmp = data->_env;
	while (data->_env)
	{
		len = size_str(delim, data->_env->key);
		if (ft_strncmp(data->_env->key, delim, len) == 0)
		{
			ptr = ft_strdup(data->_env->value + 1);
			data->_env = tmp;
			return (ptr);
		}
		data->_env = data->_env->next;
	}
	data->_env = tmp;
	return (norm_change_dollar(data, delim));
}
