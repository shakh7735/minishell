/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 03:11:27 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 03:14:21 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_env_var_make(t_data *data, char **var, char *vol)
{
	t_env	*list;

	list = list_env_search_key(data->env, var[0]);
	if (list)
	{
		if (list->vol && vol)
			free(list->vol);
		list->exp_flag = 1;
	}
	else
	{
		list = create_new_elem_list();
		list->key = ft_strdup(var[0]);
		list_env_add_back(data->env, list);
	}
	if (vol)
		list->vol = ft_strdup(vol);
	free(vol);
	free_env(var);
}

static int	valid_str(char *str)
{
	int	i;

	if (!is_my_alpha(str[0]))
		return (0);
	i = 0;
	while (str[++i])
		if (!((str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_'))
			return (0);
	return (1);
}

void	add_env_var(t_data *data, t_cmd_args *list_arg)
{
	char	**var;
	char	*vol;

	while (list_arg)
	{
		if (list_arg->arg[0])
		{
			var = ft_split_equal(list_arg->arg);
			if (!valid_str(var[0]))
			{
				free_env(var);
				ft_exit (ERR_IDENT, list_arg->arg, 0, 1);
				break ;
			}
			vol = ft_strdup(var[1]);
			while (list_arg->next && (list_arg->next->flag == '\''
					|| list_arg->next->flag == '\"'))
			{
				list_arg = list_arg->next;
				ft_my_strjoin(&vol, list_arg->arg);
			}
			add_env_var_make(data, var, vol);
		}
		list_arg = list_arg->next;
	}
}

static void	get_path(t_data *data)
{
	int		i;
	t_env	*p_list;

	p_list = list_env_search_key(data->env, "PATH");
	if (p_list)
	{
		data->path = ft_split(p_list->vol, ":");
		i = -1;
		while (data->path[++i])
			ft_my_strjoin(&data->path[i], "/");
	}
	else
		data->path = ft_split("", "");
}

char	**get_envp(t_data *data)
{
	t_env	*list;
	int		i;
	char	**temp;

	get_path(data);
	i = 0;
	list = data->env;
	while (list && ++i && list->next)
			list = list->next;
	list = data->env;
	temp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!temp)
		ft_exit (ERR_MALLOC, 0, 1, errno);
	i = 0;
	while (list)
	{
		if (list->exp_flag && list->vol)
		{
			temp[i] = ft_strjoin(list->key, "=");
			ft_my_strjoin(&temp[i], list->vol);
			temp[++i] = NULL;
		}
		list = list->next;
	}
	return (temp);
}
