/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 03:32:09 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 03:32:44 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_pwd(t_data *data)
{
	t_env	*list_pwd;
	t_env	*list_oldpwd;

	check_key_and_add(data, "PWD");
	check_key_and_add(data, "OLDPWD");
	list_pwd = list_env_search_key(data->env, "PWD");
	list_oldpwd = list_env_search_key(data->env, "OLDPWD");
	if (!list_pwd->vol)
	{
		if (list_oldpwd->vol)
			free(list_oldpwd->vol);
		list_oldpwd->vol = NULL;
		list_pwd->vol = getcwd(0, 0);
	}
	else
	{
		if (list_oldpwd->vol)
			free(list_oldpwd->vol);
		list_oldpwd->vol = ft_strdup(list_pwd->vol);
		free(list_pwd->vol);
		list_pwd->vol = getcwd(0, 0);
	}
}

static void	make_cd(t_data *data)
{
	t_env	*list;
	char	*pwd;

	if (data->cmd_args[1] && data->cmd_args[1][0] == '~')
	{
		pwd = ft_strjoin(list_vol(data->env, "HOME"), &data->cmd_args[1][1]);
		free(data->cmd_args[1]);
		data->cmd_args[1] = pwd;
	}
	if (!data->cmd_args[1])
		pwd = list_vol(data->env, "HOME");
	else if (!ft_strcmp(data->cmd_args[1], "-"))
	{
		list = list_env_search_key(data->env, "OLDPWD");
		if (!list || !list->vol)
			ft_exit(ERR_OLDPWD, 0, 0, 1);
		pwd = list->vol;
		if (list && list->vol)
			printf("%s\n", list->vol);
	}
	else
		pwd = data->cmd_args[1];
	if (chdir(pwd) == -1)
		ft_exit(ERR_FILE, data->cmd_args[1], 0, 1);
}

void	command_cd(t_data *data)
{
	if (!ft_strcmp("cd", data->cmd_args[0]))
	{
		make_cd(data);
		change_pwd(data);
	}
}

void	command_pwd(void)
{
	char	*dir;

	dir = getcwd(0, 0);
	if (!dir)
		ft_exit(ERR_PERMITION, dir, 1, errno);
	ft_putstr_fd(dir, 1);
	write(1, "\n", 1);
	free(dir);
}
