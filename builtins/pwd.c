/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:19:22 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:19:25 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	*g_status;

void	ft_pwd(void)
{
	char	*buff;

	buff = 0;
	buff = getcwd(buff, 1024);
	ft_putstr_fd(buff, 1);
	ft_putstr_fd("\n", 1);
	free(buff);
	*g_status = 0;
}
