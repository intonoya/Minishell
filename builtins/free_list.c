/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:19:10 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:19:13 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list_env(t_data *data)
{
	t_env	*tmp;

	while (data->_env)
	{
		tmp = data->_env->next;
		free(data->_env->key);
		free(data->_env->value);
		free(data->_env);
		data->_env = tmp;
	}
}

void	free_list_export(t_data *data)
{
	t_export	*tmp;

	while (data->_export)
	{
		tmp = data->_export->next;
		free(data->_export->key);
		free(data->_export->value);
		free(data->_export);
		data->_export = tmp;
	}	
}
