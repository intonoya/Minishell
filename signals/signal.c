/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:28:07 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:28:10 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	*g_status;

void	get_and_set_attr(int flag)
{
	struct termios	ts;

	tcgetattr(STDIN_FILENO, &ts);
	if (flag == 0)
	{
		ts.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &ts);
	}
	else if (flag == 1)
	{
		ts.c_lflag |= ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &ts);
	}
}

void	ft_ctrl_c(int sig_num)
{
	(void)sig_num;
	*g_status = -100;
	rl_done = 1;
}

int	ft_signal(void)
{
	get_and_set_attr(0);
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
