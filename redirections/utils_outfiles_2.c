/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_outfiles_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:26:14 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:26:17 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	norm_ft_outfiles(t_data *data, char **pipe, int j)
{
	int	i;

	i = -1;
	pipe = ft_split(data->promt, '|');
	while (pipe[++i])
		;
	i += j + 1;
	count_outfile_in_pipe(data, pipe, i, 0);
	free_array(&pipe);
}

int	norm_open_all_outfiles(t_data *data)
{
	int	x;

	x = 0;
	data->i = -1;
	while (data->info_redirect->outfiles && \
	data->info_redirect->outfiles[++data->i])
	{
		x = open(data->info_redirect->outfiles[data->i], \
		O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (x == -1)
			return (print_append_error \
			(data, data->info_redirect->outfiles[data->i]));
		close(x);
	}
	return (0);
}
