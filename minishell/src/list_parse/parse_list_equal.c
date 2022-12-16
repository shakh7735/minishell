/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list_equal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 03:15:40 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 03:16:34 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_temp_env(t_data *data, t_env *env_list)
{
	while (env_list)
	{
		chenge_vol_list(data, env_list->key, ft_strdup(env_list->vol), 0);
		env_list = env_list->next;
	}
}

static void	fill_values_env(t_env *env, t_cmd_args **list_arg, char **s)
{
	t_cmd_args	*list;
	char		*vol;

	list = *list_arg;
	env->exp_flag = 0;
	env->key = ft_strdup(s[0]);
	vol = ft_strdup(s[1]);
	while (list->next && (list->next->flag == '\'' || list->next->flag == '\"'))
	{
		list->flag = 'd';
		list = list->next;
		ft_my_strjoin(&vol, list->arg);
	}
	env->vol = ft_strdup(vol);
	free(vol);
	list->flag = 'd';
	list = list->next;
	*list_arg = list;
}

static int	equal_and_first_alpha(t_env **env_tmp, t_cmd_args **list)
{
	char	**s;
	t_env	*env_list;

	s = ft_split_equal((*list)->arg);
	env_list = create_new_elem_list();
	fill_values_env(env_list, list, s);
	free_env(s);
	if (!(*env_tmp))
		*env_tmp = env_list;
	else
		list_env_add_back(*env_tmp, env_list);
	return (0);
}

static void	check_make_equal(t_data *data, t_cmd_args *list, int main)
{
	int		i;
	t_env	*env_list;

	env_list = NULL;
	i = -1;
	while (list)
	{
		if (list->arg[0] == 0)
		{
			list = list->next;
			continue ;
		}
		else if (list->flag || !ft_my_strchr(list->arg, '='))
			;
		else if (!is_my_alpha(list->arg[0]))
			;
		else if (!equal_and_first_alpha(&env_list, &list))
			continue ;
		free_list(&env_list);
		return ;
	}
	if (!main)
		change_temp_env(data, env_list);
	free_list(&env_list);
}

void	equal_exist(t_data *data, t_cmd_args **temp, int main)
{
	t_cmd_args	*list;

	check_make_equal(data, *temp, main);
	list = *temp;
	while (list && (list->arg[0] == 0 || list->flag == 'd'))
		list = list->next;
	if (list && list->next && !ft_strcmp("export", list->arg))
	{
		if (!main)
			add_env_var(data, list->next);
		free_list_arg(temp);
	}
}
