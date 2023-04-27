/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:18:32 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:18:35 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	*g_status;

int	check_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-' && str[1] == 'n')
	{
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (0);
		return (-1);
	}
	return (-1);
}

void	n_ft_echo(char **ptr, int flag, int i, char *str2)
{
	while (ptr[i])
	{
		str2 = correct_heredoc_name(ptr[i], 0, 0);
		ft_putstr_fd(str2, 1);
		if (ptr[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
		free(str2);
	}
	if (flag == 0)
		write(1, "\n", 1);
}

void	ft_echo(char *str, char **ptr, char *str2, int i)
{
	int		flag;

	ptr = ft_split(str, ' ');
	flag = 0;
	while (ptr[++i])
	{
		str2 = correct_heredoc_name(ptr[i], 0, 0);
		if (check_flag(str2) != 0)
		{
			free(str2);
			break ;
		}
		free(str2);
	}
	if (i != 0)
		flag = 1;
	n_ft_echo(ptr, flag, i, str2);
	free_array(&ptr);
	*g_status = 0;
}
