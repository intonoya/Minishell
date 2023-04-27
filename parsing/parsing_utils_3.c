/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:12:42 by intonoya          #+#    #+#             */
/*   Updated: 2023/03/30 16:12:45 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*clear_str(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	len = ft_strlen(str);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (!tmp || !str)
		return (0);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			tmp[j] = str[i];
			j++;
		}
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void	norm_split_pipes(t_data *data, int j, int flag)
{
	if (j == 0 && flag == 0)
	{
		if (data->info_parsing->flag_for_prelast_redirect[j] == _outfile)
			dup2(data->info_redirect->fd_outfiles[0], STDOUT_FILENO);
		else if (data->info_parsing->flag_for_prelast_redirect[j] == _append)
			dup2(data->info_redirect->fd_append[0], STDOUT_FILENO);
		else if (data->info_parsing->flag_for_prelast_redirect[j] == _infile)
			dup2(data->info_redirect->fd_infiles[0], STDIN_FILENO);
	}
	else
	{
		if (data->info_parsing->flag_for_prelast_redirect[j] == _outfile)
			dup2(data->info_redirect->fd_outfiles \
			[data->info_parsing->index_outfile], STDOUT_FILENO);
		else if (data->info_parsing->flag_for_prelast_redirect[j] == _append)
			dup2(data->info_redirect->fd_append \
			[data->info_parsing->index_append], STDOUT_FILENO);
		else if (data->info_parsing->flag_for_prelast_redirect[j] == _infile)
			dup2(data->info_redirect->fd_infiles \
			[data->info_parsing->index_infile], STDIN_FILENO);
	}
}

void	continue_split_pipes(t_data *data, char *built, int j, char *check)
{
	int		k;

	(void)j;
	k = size_str(check, "export");
	if (ft_strncmp(check, "export", k) == 0)
		ft_export(data, built + 6);
	k = size_str(check, "unset");
	if (ft_strncmp(check, "unset", k) == 0)
		ft_unset(data, built + 6);
	k = size_str(check, "exit");
	if (ft_strncmp(check, "exit", k) == 0)
		ft_exit(data, built + 5);
	k = size_str(check, "echo");
	if (ft_strncmp(check, "echo", k) == 0)
		ft_echo(built + 5, 0, 0, -1);
	k = size_str(check, "env");
	if (ft_strncmp(check, "env", k) == 0)
		ft_env(data);
}

void	continue_split_pipes_2(t_data *data, char **splited_pipe, char *built)
{
	char	*check;
	int		k;

	check = 0;
	k = 0;
	data->i = 0;
	check = correct_heredoc_name(splited_pipe[data->i], 0, 0);
	k = size_str(check, "pwd");
	if (ft_strncmp(check, "pwd", k) == 0)
		ft_pwd();
	k = size_str(check, "cd");
	if (ft_strncmp(check, "cd", k) == 0)
		ft_cd(data, splited_pipe[data->i + 1]);
	else
		continue_split_pipes(data, built, data->i, check);
	my_free(&check);
}

void	split_pipes(t_data *data, char *str, int j, int flag)
{
	char	**splited_promt;
	char	**splited_pipe;

	splited_pipe = 0;
	splited_promt = 0;
	data->i = 0;
	splited_promt = ft_split(data->promt, '|');
	if (splited_promt[j])
	{
		splited_pipe = ft_split(str, ' ');
		if (data->info_parsing->flag_for_prelast_redirect[j] != _default)
			norm_split_pipes(data, j, flag);
		if (splited_pipe[data->i])
			continue_split_pipes_2(data, splited_pipe, splited_promt[j]);
		if (flag == 0 && j == 0 && \
		data->info_parsing->flag_for_prelast_redirect[j] != _default)
			dup2(data->info_pipe->output, STDOUT_FILENO);
	}
	free_array(&splited_pipe);
	free_array(&splited_promt);
}
