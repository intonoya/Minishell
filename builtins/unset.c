/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:19:32 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:19:35 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	*g_status;

void	display_error_for_unset(char *error)
{
	char	*str;

	str = correct_heredoc_name(error, 0, 0);
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	free(str);
	*g_status = 1;
}

int	check_argument(char *str, char *for_error)
{
	int	i;

	i = -1;
	if (!str || (str[0] >= '0' && str[0] <= '9'))
	{
		display_error_for_unset(for_error);
		return (-1);
	}
	while (str[++i])
	{
		if (!(str[i] >= 'a' && str[i] <= 'z') && \
		!(str[i] >= 'A' && str[i] <= 'Z') && !(str[i] >= '0' && str[i] <= '9'))
		{
			if (str[i] == '\'' || str[i] == '\"' || str[i] == '_')
				continue ;
			if (i > 0 && str[i] == '+' && str[i + 1] == '\0')
				return (0);
			else
			{
				display_error_for_unset(for_error);
				return (-1);
			}
		}
	}
	return (0);
}

void	unset_export(t_data *data, char *str)
{
	t_export	*tmp;
	int			len;

	tmp = data->_export;
	while (data->_export)
	{
		len = size_str(str, data->_export->key);
		if (ft_strncmp(str, data->_export->key, len) == 0)
		{
			data->_export->flag = 1;
			break ;
		}
		data->_export = data->_export->next;
	}
	data->_export = tmp;
}

void	unset_env(t_data *data, char *str)
{
	t_env	*tmp;
	int		len;

	tmp = data->_env;
	while (data->_env)
	{
		len = size_str(str, data->_env->key);
		if (ft_strncmp(str, data->_env->key, len) == 0)
		{
			data->_env->flag = 1;
			break ;
		}
		data->_env = data->_env->next;
	}
	data->_env = tmp;
}

void	ft_unset(t_data *data, char *str)
{
	char	**ptr;
	char	**res;
	int		i;

	if (!str || !*str)
		return ;
	ptr = ft_split(str, ' ');
	i = -1;
	while (ptr[++i])
	{
		res = ft_split(ptr[i], '=');
		if (check_argument(res[0], ptr[i]) == 0)
		{
			unset_env(data, res[0]);
			unset_export(data, res[0]);
			*g_status = 0;
		}
		free_array(&res);
	}
	free_array(&ptr);
}
