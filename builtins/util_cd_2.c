/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_cd_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:19:57 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:19:59 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	*g_status;

char	*find_pwd_export(t_data *data)
{
	t_export	*tmp;
	char		*pwd;
	int			len;

	tmp = data->_export;
	pwd = 0;
	while (data->_export)
	{
		len = size_str("PWD", data->_export->key);
		if (ft_strncmp("PWD", data->_export->key, len) == 0)
		{
			pwd = ft_strdup(data->_export->value);
			break ;
		}
		data->_export = data->_export->next;
	}
	data->_export = tmp;
	return (pwd);
}
