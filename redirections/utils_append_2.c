/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_append_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:25:23 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:25:26 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	continue_open_all_append(t_data *data, int x)
{
	if (data->info_redirect->outfiles && data->info_redirect->outfiles[x] == 0)
		while (data->info_redirect->outfiles && \
		data->info_redirect->outfiles[x] == 0)
			x--;
	data->info_redirect->fd_append[data->i] = \
	open(data->info_redirect->append[x], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (data->info_redirect->fd_append[data->i] == -1)
		return (print_append_error(data, data->info_redirect->append[x]));
	data->j++;
	data->i++;
	return (0);
}
