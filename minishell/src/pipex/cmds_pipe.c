/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 03:07:48 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 03:07:52 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	make_exec(t_data *data)
{
	char	*command;
	int		i;
	char	**envp;

	envp = get_envp(data);
	i = -1;
	while (data->path[++i])
	{
		command = ft_strjoin(data->path[i], data->cmd_args[0]);
		if (access(command, X_OK) == 0)
			break ;
		free(command);
	}
	if (!data->path[i])
		chenge_vol_list(data, "_", data->cmd_args[0], 1);
	else
		chenge_vol_list(data, "_", command, 1);
	unlink(HEREDOC);
	if (!data->path[i])
		execve(data->cmd_args[0], data->cmd_args, envp);
	else
		execve(command, data->cmd_args, envp);
	free_env (envp);
	errno = 127;
	ft_exit(ERR_COMMAND, data->cmd_args[0], 1, 127);
}

static int	check_command(t_data *data)
{
	char	*com;

	com = str_to_lowercase(data->cmd_args[0]);
	if (!data->cmd_args)
		return (0);
	if (!ft_strcmp("pwd", com))
		command_pwd();
	else if (!ft_strcmp("cd", com)
		|| !ft_strcmp("unset", data->cmd_args[0])
		|| !ft_strcmp("exit", data->cmd_args[0]))
		;
	else if (!ft_strcmp("echo", com))
		command_echo(data);
	else if (!ft_strcmp("export", data->cmd_args[0]))
		command_export(data);
	else
		make_exec(data);
	free(com);
	free_env(data->cmd_args);
	return (1);
}

static void	pipe_and_fork(t_data *data, int id, int *fd)
{
	if (data->cmds[id + 1])
	{
		if (pipe(fd) == -1)
			ft_exit(ERR_PIPE, 0, 1, errno);
		data->pid[id] = fork();
		if (data->pid[id] == -1)
			ft_exit(ERR_FORK, 0, 1, errno);
	}
	else
	{
		if (data->fd_out)
		{
			if (dup2(data->fd_out, STDOUT_FILENO) == -1)
				ft_exit(ERR_DUP, 0, 1, errno);
			close(data->fd_out);
		}
		if (data->fd_in)
		{
			if (dup2(data->fd_in, STDIN_FILENO) == -1)
				ft_exit(ERR_DUP, 0, 1, errno);
			close(data->fd_in);
		}
		check_command (data);
		exit (errno);
	}
}

static void	cmd_child(t_data *data, int fd[2])
{
	if (!data->fd_out)
		dup2(fd[1], STDOUT_FILENO);
	else
		dup2(data->fd_out, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (data->fd_in)
		close(data->fd_in);
	if (data->fd_out)
		close(data->fd_out);
	check_command (data);
	exit (errno);
}

void	cmd_pipe(t_data *data, int id)
{
	int	fd[2];

	errno = 0;
	if (id)
	{
		data->fd_in = 0;
		data->fd_out = 0;
		data->cmd_args = init_cmd_to_list(data, data->cmds[id], 1);
	}
	pipe_and_fork(data, id, fd);
	if (data->pid[id] == 0)
		cmd_child(data, fd);
	else
	{
		if (!data->fd_in)
			dup2(fd[0], STDIN_FILENO);
		else
			dup2(data->fd_in, STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		if (data->fd_out)
			close(data->fd_out);
		free_mtx(data->cmd_args);
	}
}
