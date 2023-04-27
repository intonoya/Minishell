/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:08:41 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:08:48 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	norm_change_shlvl_in_export(t_data *data, char *new_shlvl, char *str, \
									int shlvl)
{
	shlvl = ft_atoi(str);
	shlvl++;
	if (shlvl > 1000)
		shlvl = 1;
	else if (shlvl == 1000)
		shlvl = 0;
	free(data->_export->value);
	data->_export->value = 0;
	new_shlvl = ft_itoa(shlvl);
	if (shlvl == 0)
	{
		data->_export->value = ft_strdup("\"");
		data->_export->value = ft_strjoin(data->_export->value, "\"");
	}
	else
	{
		data->_export->value = ft_strdup("=");
		data->_export->value = ft_strjoin(data->_export->value, "\"");
		data->_export->value = \
		ft_strjoin(data->_export->value, new_shlvl);
		data->_export->value = ft_strjoin(data->_export->value, "\"");
	}
	free(new_shlvl);
	new_shlvl = 0;
}

void	change_shlvl_in_export(t_data *data, char *check, \
		char *str, char *new_shlvl)
{
	t_export	*tmp;
	int			len;

	len = 0;
	tmp = data->_export;
	while (data->_export)
	{
		len = size_str(data->_export->key, "SHLVL");
		if (ft_strncmp(data->_export->key, "SHLVL", len) == 0)
		{
			check = correct_heredoc_name(data->_export->value + 1, 0, 0);
			str = ft_strdup(check);
			norm_change_shlvl_in_export(data, new_shlvl, str, 0);
			break ;
		}
		data->_export = data->_export->next;
	}
	data->_export = tmp;
	free(check);
	free(str);
	str = 0;
	check = 0;
}
