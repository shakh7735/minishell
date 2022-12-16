/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list_env2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:19:58 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 19:20:45 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*go_first_point(t_env *list)
{
	while (list)
	{
		if (list->prev)
			list = list->prev;
		else
			break ;
	}
	return (list);
}

t_env	*ft_copy_list(t_env *list)
{
	t_env	*ret;

	if (!list)
		return (NULL);
	ret = (t_env *)malloc(sizeof(t_env));
	if (!ret)
		ft_exit(ERR_MALLOC, 0, 1, errno);
	ret->prev = NULL;
	ret->next = NULL;
	ret->key = ft_strdup (list->key);
	ret->vol = ft_strdup (list->vol);
	ret->exp_flag = list->exp_flag;
	return (ret);
}

void	init_ft_env(t_data *data, char **env)
{
	t_env	*list;
	t_env	*prev;
	char	**temp;
	int		i;

	i = -1;
	prev = NULL;
	while (env[++i])
	{
		temp = ft_split_equal(env[i]);
		list = create_new_elem_list();
		list->prev = prev;
		if (prev)
			prev->next = list;
		list->key = ft_strdup(temp[0]);
		if (!ft_strcmp(temp[0], "OLDPWD"))
			list->vol = NULL;
		else if (!ft_strcmp(temp[0], "SHLVL"))
			list->vol = ft_itoa(ft_my_atoi(temp[1]) + 1);
		else
			list->vol = ft_strdup(temp[1]);
		prev = list;
		free_env(temp);
	}
	data->env = go_first_point(list);
}

void	free_list(t_env **list)
{
	t_env	*temp;

	temp = *list;
	while (temp && temp->prev)
		temp = temp->prev;
	while (temp)
	{
		if (temp->key)
			free(temp->key);
		if (temp->vol)
			free(temp->vol);
		if (temp->next)
		{
			temp = temp->next;
			free(temp->prev);
		}
		else
		{
			free(temp);
			temp = NULL;
		}
	}
}
