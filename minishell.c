/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:35:44 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:35:51 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	*g_status;

int	size_str(char *s1, char *s2)
{
	int	len_s1;
	int	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s1 > len_s2)
		return (len_s1);
	return (len_s2);
}

void	my_free(char **for_free)
{
	free(*for_free);
	*for_free = 0;
}

int	check_promt(t_data *data)
{
	if (!data->promt)
		get_exit(data);
	if (*g_status == -100)
	{
		*g_status = 1;
		free_all(data, 1);
		my_free(&data->promt);
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	data = init_lists(argc, argv, env, &data);
	g_status = malloc(sizeof(int));
	data.error_code = g_status;
	*g_status = *data.error_code;
	*g_status = 0;
	change_shlvl(&data);
	while (1)
	{
		ft_signal();
		init_structure(&data);
		data.promt = readline("Minishell$  ");
		if (check_promt(&data) == -1)
			continue ;
		data.for_history = ft_strdup(data.promt);
		parsing(&data);
		if (ft_strlen(data.for_history) > 0)
			add_history(data.for_history);
		free(data.promt);
		free(data.for_history);
		close_all_fds(&data);
		free_all(&data, 1);
	}
	return (0);
}
