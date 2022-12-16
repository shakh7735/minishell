/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 03:27:44 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 03:28:23 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_list_add(t_cmd_args **list)
{
	t_cmd_args	*node;

	node = malloc(sizeof(t_cmd_args));
	if (!node)
		return ;
	node->flag = 0;
	node->arg = NULL;
	node->next = NULL;
	node->prev = *list;
	if (*list)
		(*list)->next = node;
	*list = node;
}

void	new_list_arg(t_cmd_args **list, char *arg)
{
	t_cmd_args	*node;

	node = malloc(sizeof(t_cmd_args));
	if (!node)
		return ;
	node->flag = 0;
	node->arg = ft_strdup(arg);
	if (*list)
	{
		node->next = (*list)->next;
		(*list)->next = node;
	}
	else
		node->next = NULL;
	node->prev = *list;
	if (node->next)
		node->next->prev = node;
	*list = node;
}

void	delete_list_arg(t_cmd_args **list)
{
	t_cmd_args	*node;

	if ((*list)->prev)
		(*list)->prev->next = (*list)->next;
	node = *list;
	*list = (*list)->next;
	if (*list)
		(*list)->prev = node->prev;
	free(node->arg);
	free(node);
}

void	free_list_arg(t_cmd_args **list)
{
	t_cmd_args	*temp;

	while (*list)
	{
		temp = (*list)->next;
		if ((*list)->arg)
			free((*list)->arg);
		free(*list);
		*list = temp;
	}
	*list = NULL;
}

void	free_list_cmd_args(t_cmd_args *list)
{
	t_cmd_args	*node;

	while (list && list->prev)
		list = list->prev;
	while (list)
	{
		node = list->next;
		if (list->arg)
			free(list->arg);
		free(list);
		list = node;
	}
}
