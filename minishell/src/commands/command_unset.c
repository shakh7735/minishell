/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 03:07:37 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 03:07:42 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	list_env_del_elem(t_env *env, char *key)
{
	t_env	*temp;
	t_env	*p;
	t_env	*n;

	temp = list_env_search_key (env, key);
	if (!temp)
		return ;
	p = temp->prev;
	n = temp->next;
	if (p)
		p->next = n;
	else
		n->prev = NULL;
	if (n)
		n->prev = p;
	else
		p->next = NULL;
	if (temp->vol)
		free (temp->vol);
	free (temp->key);
	free (temp);
}

void	command_unset(t_data *data)
{
	int	n;

	if (data->cmds[1] || ft_strcmp("unset", data->cmd_args[0]))
		return ;
	n = 0;
	while (data->cmd_args[++n])
		list_env_del_elem(data->env, data->cmd_args[n]);
}
