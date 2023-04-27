/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:28:31 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:28:36 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_struct_pipe(t_data *data)
{
	free_array(&data->info_pipe->split_space);
	free_array(&data->info_pipe->split_pipe);
	free_array(&data->info_pipe->cmd_args);
	free_array(&data->info_pipe->path);
	free(data->info_pipe->cmd);
	free(data->info_pipe->pid);
	free(data->info_pipe->fd);
}

void	free_struct_redirection(t_data *data)
{
	free(data->info_redirect->count_outfiles_in_pipe);
	free(data->info_redirect->count_infiles_in_pipe);
	free(data->info_redirect->heredoc_count_in_pipe);
	free(data->info_redirect->count_append_in_pipe);
	free_array(&data->info_redirect->heredoc_name);
	free_array(&data->info_redirect->outfiles);
	free_array(&data->info_redirect->heredoc);
	free_array(&data->info_redirect->infiles);
	free_array(&data->info_redirect->append);
	free(data->info_redirect->fd_outfiles);
	free(data->info_redirect->fd_infiles);
	free(data->info_redirect->fd_heredoc);
	free(data->info_redirect->fd_append);
}

void	free_array(char ***str)
{
	int	i;

	i = 0;
	if (*str)
	{
		while ((*str)[i])
		{
			free((*str)[i]);
			(*str)[i] = 0;
			i++;
		}
		free(*str);
		*str = 0;
	}
}
