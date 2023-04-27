/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_outfiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:26:22 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:26:26 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	continue_open_all_outfiles(t_data *data, int x)
{
	if (data->info_redirect->outfiles && data->info_redirect->outfiles[x] == 0)
		while (data->info_redirect->outfiles && \
		data->info_redirect->outfiles[x] == 0)
			x--;
	data->info_redirect->fd_outfiles[data->i] = \
	open(data->info_redirect->outfiles[x], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->info_redirect->fd_outfiles[data->i] == -1)
		return (print_append_error(data, data->info_redirect->outfiles[x]));
	data->j++;
	data->i++;
	return (0);
}

void	count_outfile_in_pipe(t_data *data, char **pipe, int k, int count)
{
	data->i = -1;
	data->info_redirect->fd_outfiles = malloc(sizeof(int) * k);
	data->info_redirect->count_outfiles_in_pipe = malloc(sizeof(int) * k);
	count = -1;
	while (++count < k)
	{
		data->info_redirect->fd_outfiles[count] = -1;
		data->info_redirect->count_outfiles_in_pipe[count] = -1;
	}
	while (pipe && pipe[++data->i])
	{
		data->j = 0;
		count = 0;
		while (pipe[data->i][data->j])
		{
			if (pipe[data->i][data->j] == '>' && \
			pipe[data->i][data->j + 1] == '>')
				data->j++;
			else if (pipe[data->i][data->j] == '>' && \
			pipe[data->i][data->j + 1] != '>')
				count++;
			data->j++;
		}
		data->info_redirect->count_outfiles_in_pipe[data->i] = count;
	}
}

int	check_count_last_outfiles(int pos, char *pipe)
{
	int	i;

	i = 0;
	if (pos > 0)
	{
		if (pos > 1)
		{
			i = -1;
			while (pos >= 1 && pipe[++i])
				if (pipe[i] == '>' && (pipe[i + 1] && pipe[i + 1] != '>'))
					pos--;
		}
		return (1);
	}
	return (0);
}

int	open_all_outfiles(t_data *data, int count_pipe, int x, int check)
{
	data->i = 0;
	data->j = 0;
	while (data->info_redirect->outfiles && count_pipe > 0)
	{
		check++;
		if (data->info_redirect->count_outfiles_in_pipe && \
		data->info_redirect->count_outfiles_in_pipe[data->j] == 0)
		{
			count_pipe--;
			check = 0;
			data->j++;
		}
		else if (data->info_redirect->count_outfiles_in_pipe && \
		(check == data->info_redirect->count_outfiles_in_pipe[data->j]))
		{
			if (continue_open_all_outfiles(data, x) == -1)
				return (-1);
			check = 0;
			count_pipe--;
		}
		x++;
	}
	if (norm_open_all_outfiles(data) == -1)
		return (-1);
	return (0);
}
