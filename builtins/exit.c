/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:18:51 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:18:53 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	*g_status;

void	print_error(t_data *data, char *for_error)
{
	ft_putstr_fd("exit\nminishell: exit: ", 1);
	ft_putstr_fd(for_error, 1);
	ft_putstr_fd(": numeric argument required\n", 1);
	free_all(data, 0);
	exit(255);
}

void	check_first_argument(t_data *data, char *str)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			flag = 1;
		i++;
	}
	if (str[i] == '\0')
		print_error(data, str);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			print_error(data, str);
		i++;
	}
	if (ft_strlen(str) > 19)
		print_error(data, str);
	if (ft_strncmp(str, "9223372036854775807", 19) > 0)
		print_error(data, str);
	if (flag == 1 && ft_strncmp(str + 1, "9223372036854775808", 19) > 0)
		print_error(data, str);
}

int	check_count_arguments(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	if (i == 1)
		return (-1);
	ft_putstr_fd("minishell: exit: too many arguments\n", 1);
	*g_status = 1;
	return (0);
}

void	cast_and_exit(t_data *data, char *str)
{
	unsigned char	for_exit;

	(void)data;
	for_exit = ft_atoi(str);
	ft_putstr_fd("exit\n", 1);
	free_all(data, 0);
	exit(for_exit);
}

void	ft_exit(t_data *data, char *str)
{
	char	**ptr;
	int		for_exit;
	char	*str2;

	ptr = 0;
	ptr = ft_split(str, ' ');
	for_exit = *g_status;
	str2 = 0;
	if (ptr && ptr[0])
	{
		str2 = correct_heredoc_name(ptr[0], 0, 0);
		check_first_argument(data, str2);
		if (check_count_arguments(ptr) == 0)
		{
			free_array(&ptr);
			return ;
		}
		cast_and_exit(data, str2);
	}
	free_all(data, 0);
	free_array(&ptr);
	ft_putstr_fd("exit\n", 1);
	exit(for_exit);
}
