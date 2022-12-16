/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:12:46 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 19:14:22 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_str_compaire(char *s1, char *s2)
{
	int	i;

	if (s1 && !s2)
		return (1);
	else if (!s1 && s2)
		return (-1);
	else if (!s1 && !s2)
		return (0);
	i = -1;
	while (++i > -1)
	{
		if (s1[i] && s2[i] && s1[i] != s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] && !s2[i])
			return (1);
		else if (!s1[i] && s2[i])
			return (-1);
		else if (!s1[i] && !s2[i])
			return (0);
	}
	return (0);
}

static int	ft_list_elem_compaire(t_env *elem1, t_env *elem2)
{
	t_env	*temp;

	if (ft_str_compaire(elem1->key, elem2->key) > 0)
	{
		temp = elem1->prev;
		elem1->prev = elem1->next;
		elem1->next = elem2->next;
		elem2->next = elem1;
		elem2->prev = temp;
		if (temp)
			temp->next = elem2;
		if (elem1->next)
			elem1->next->prev = elem1;
		return (1);
	}
	return (0);
}

static t_env	*ft_copy_list_ar(t_env *env)
{
	t_env	*temp;
	t_env	*prev;

	prev = NULL;
	temp = NULL;
	while (env)
	{
		if (temp)
			temp = temp->next;
		temp = ft_copy_list(env);
		env = env->next;
		if (prev)
			prev->next = temp;
		temp->prev = prev;
		prev = temp;
	}
	temp = go_first_point(temp);
	return (temp);
}

static t_env	*sort_list(t_env *env)
{
	t_env	*temp;

	temp = ft_copy_list_ar(env);
	while (temp && temp->next)
	{
		if (ft_list_elem_compaire(temp, temp->next))
			temp = go_first_point(temp);
		else
		{
			if (temp->next)
				temp = temp->next;
			else
				break ;
		}
	}
	temp = go_first_point(temp);
	return (temp);
}

void	command_export(t_data *data)
{
	t_env	*list;

	list = sort_list (data->env);
	while (list)
	{
		if (list->exp_flag)
		{
			if (!ft_strcmp(list->key, "_"))
				;
			else if (list->vol)
				printf("declare -x %s=\"%s\"\n", list->key, list->vol);
			else
				printf("declare -x %s\n", list->key);
		}
		if (!list->next)
			break ;
		list = list->next;
	}
	free_list(&list);
}
