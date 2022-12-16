/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 03:26:19 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 03:27:31 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**pipe_split(char *str, int pipe_b, char c, int i[2])
{
	char	**pipe_cmd;

	pipe_cmd = malloc(sizeof(pipe_cmd) * (pipe_count(str) + 1));
	if (!pipe_cmd)
		ft_exit(ERR_MALLOC, 0, 1, errno);
	while (str[i[0]])
	{
		while (str[i[0]] && !c)
		{
			if (str[i[0]] == '\'' || str[i[0]] == '\"')
				c = str[i[0]++];
			else if (str[i[0]++] == '|' && str[i[0]])
			{
				pipe_cmd[i[1]++] = ft_substr(str, pipe_b, i[0] - 1 - pipe_b);
				pipe_b = i[0];
			}
		}
		while (str[i[0]] && str[i[0]] != c)
			i[0]++;
		if (str[i[0]])
			c = 0 * i[0]++;
	}
	pipe_cmd[i[1]++] = ft_substr(str, pipe_b, i[0] - pipe_b);
	pipe_cmd[i[1]] = NULL;
	return (pipe_cmd);
}

static void	pipex_make(t_data *data)
{
	int	pid;
	int	ret;
	int	id;

	errno = 0;
	ret = 1;
	pid = fork();
	if (pid == -1)
		ft_exit(ERR_FORK, 0, 1, errno);
	if (!pid)
	{
		id = -1;
		while (data->cmds[++id])
			cmd_pipe(data, id);
		id = -1;
		while (data->cmds[++id + 1])
			waitpid(data->pid[id], &ret, 0);
		get_errno(ret);
		exit(errno);
	}
	waitpid(pid, &ret, 0);
	get_errno(ret);
	free(data->pid);
	free_mtx(data->cmd_args);
}

char	*list_vol(t_env *env, char *key)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (!ft_strcmp(temp->key, key))
			break ;
		temp = temp->next;
	}
	if (!temp)
		return (NULL);
	return (temp->vol);
}

static int	pipex_init(t_data *data, char *line)
{
	char	*com;

	if (data->fd_out != -1 && data->fd_in != -1)
	{
		com = str_to_lowercase(data->cmd_args[0]);
		if (!data->cmds[1])
		{
			if (ft_strcmp("echo", com)
				|| !ft_strcmp("", list_vol(data->env, "_")))
				chenge_vol_list(data, "_", ft_strdup(data->cmd_args[0]), 1);
		}
		else
			chenge_vol_list(data, "_", ft_strdup(""), 1);
		free(com);
		command_exit(data);
		command_cd(data);
		command_unset(data);
		data->pid = malloc(sizeof(data->pid) * pipe_count(line));
		if (!data->pid)
			ft_exit(ERR_MALLOC, 0, 1, errno);
		return (0);
	}
	free_mtx(data->cmd_args);
	return (1);
}

void	pipex(t_data *data, char *line)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	data->cmds = pipe_split(line, 0, 0, i);
	if (!data->cmds)
		return ;
	data->cmd_args = init_cmd_to_list(data, data->cmds[0], 0);
	if (data->cmd_args && !pipex_init(data, line) && !errno)
		pipex_make(data);
	free_mtx(data->cmds);
}
