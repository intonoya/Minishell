/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:20:14 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:20:18 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	*g_status;

void	first_double_quote(char *str, int *j)
{
	str[*j] = '\"';
	(*j)++;
}

void	dup_for_export(char *str, char *value, int *i, int *j)
{
	str[*j] = value[*i];
	(*i)++;
	(*j)++;
}

void	display_error_for_export(char *error)
{
	char	*str;

	str = correct_heredoc_name(error, 0, 0);
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	free(str);
	*g_status = 1;
}

int	check_variable(char *str, char *for_error)
{
	int	i;

	i = -1;
	if (!str || (str[0] >= '0' && str[0] <= '9'))
	{
		display_error_for_export(for_error);
		return (-1);
	}
	while (str[++i])
	{
		if (!(str[i] >= 'a' && str[i] <= 'z') && \
		!(str[i] >= 'A' && str[i] <= 'Z') && !(str[i] >= '0' && str[i] <= '9'))
		{
			if (str[i] == '_')
				continue ;
			if (i > 0 && str[i] == '+' && str[i + 1] == '\0')
				return (0);
			else
			{
				display_error_for_export(for_error);
				return (-1);
			}
		}
	}
	return (0);
}

void	check_and_add_variables(t_data *data, char *str)
{
	char	**ptr;
	char	**res;
	int		i;

	ptr = ft_split(str, ' ');
	res = 0;
	i = -1;
	while (ptr[++i])
	{
		res = ft_split(ptr[i], '=');
		if (check_variable(res[0], ptr[i]) == 0)
		{
			if (check_add_env(ptr[i]) == 0)
				add_variable_env(data, ptr[i]);
			add_variable_export(data, ptr[i]);
		}
		free_array(&res);
	}
	free_array(&ptr);
}
