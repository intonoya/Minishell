/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_export_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:20:25 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:20:29 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_double_quotes_once_export(char *str, char *str2, int i, int j)
{
	if (!str)
		return (0);
	if (ft_strlen(str) == 1)
	{
		str2 = malloc(sizeof(char) * 4);
		str2[0] = '=';
		str2[1] = '\"';
		str2[2] = '\"';
		str2[3] = '\0';
	}
	else
	{		
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
	}
	return (str2);
}

void	norm_check_key_export(t_export *_export, char *str)
{
	free(_export->value);
	_export->value = ft_strdup(str);
}
