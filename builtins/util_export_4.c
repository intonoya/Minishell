/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_export_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:20:51 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:20:56 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_empty_value(void)
{
	char	*str;

	str = malloc(sizeof(char) * 4);
	str[0] = '=';
	str[1] = '\"';
	str[2] = '\"';
	str[3] = '\0';
	return (str);
}

char	*norm_add_double_quote(t_data *data, int i, int j)
{
	char	*str;

	if (!data->_export->value)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(data->_export->value) + 3));
	while (data->_export->value[i])
	{
		if (i == 1 && j == 1)
			first_double_quote(str, &j);
		else
			dup_for_export(str, data->_export->value, &i, &j);
	}
	str[j] = '\"';
	str[j + 1] = '\0';
	return (str);
}

char	*add_double_quotes_once(char *str)
{
	char	*str2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	str2 = malloc(sizeof(char) * (ft_strlen(str) + 3));
	while (str[i])
	{
		if (i == 1 && j == 1)
			first_double_quote(str2, &j);
		else
			dup_for_export(str2, str, &i, &j);
	}
	str2[j] = '\"';
	str2[j + 1] = '\0';
	return (str2);
}

char	*strdup_for_export(char *str)
{
	char	*ptr;
	int		i;
	int		len;

	ptr = malloc(sizeof(char) * ft_strlen(str));
	i = 0;
	len = ft_strlen(str) - 1;
	while (i < len)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	add_plus_and_equal_export(t_data *data, char *str)
{
	t_export	*tmp;
	char		**ptr;

	tmp = data->_export;
	while (data->_export->next)
		data->_export = data->_export->next;
	data->_export->next = malloc(sizeof(t_export));
	data->_export = data->_export->next;
	data->_export->next = 0;
	ptr = ft_split(str, '+');
	data->_export->key = ft_strdup(ptr[0]);
	data->_export->value = add_double_quotes_once_export \
	(first_equal(str), 0, 0, 0);
	data->_export->flag = 0;
	data->_export = tmp;
	free_array(&ptr);
	sort_export(data);
}
