/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 03:28:36 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 03:29:25 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_env_add_back(t_env *env, t_env *new)
{
	while (env->next)
		env = env->next;
	env->next = new;
	new->prev = env;
}

t_env	*list_env_search_key(t_env *env, char *key)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (!ft_strcmp(temp->key, key))
			break ;
		temp = temp->next;
	}
	return (temp);
}

t_env	*create_new_elem_list(void)
{
	t_env	*el;

	el = (t_env *)malloc(sizeof(t_env));
	if (!el)
		ft_exit(ERR_MALLOC, 0, 1, errno);
	el->exp_flag = 1;
	el->prev = NULL;
	el->next = NULL;
	el->key = NULL;
	el->vol = NULL;
	return (el);
}

int	check_key_and_add(t_data *data, char *key)
{
	t_env	*list;

	list = list_env_search_key(data->env, key);
	if (list)
		return (1);
	list = create_new_elem_list();
	list->key = ft_strdup(key);
	list_env_add_back(data->env, list);
	return (0);
}

void	chenge_vol_list(t_data *data, char *key, char *vol, int flag)
{
	t_env	*list;

	if (!check_key_and_add(data, key))
	{
		list = list_env_search_key(data->env, key);
		if (list->vol)
			free(list->vol);
		list->vol = vol;
		list->exp_flag = flag;
	}
	else
	{
		list = list_env_search_key(data->env, key);
		if (list->vol)
			free(list->vol);
		list->vol = vol;
	}
}
