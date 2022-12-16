/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 03:17:19 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 03:26:01 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	p_file(t_data *data, t_cmd_args **list, t_cmd_args **node, int main)
{
	while (*list)
	{
		if ((*list)->arg[0] && !(*list)->flag && ((*list)->arg[0] == '<'
				|| (*list)->arg[0] == '>'))
		{
			*node = (*list)->prev;
			if ((!(*list)->arg[1]
					|| ((*list)->arg[0] == (*list)->arg[1] && !(*list)->arg[2]))
				&& (*list)->next && (*list)->next->next)
			{
				*node = (*list)->next;
				*list = (*list)->next->next;
				check_in_out(data, (*list)->prev->prev, list, main);
			}
			else
				check_in_out(data, *list, list, main);
		}
		else
		{
			*node = *list;
			*list = (*list)->next;
		}
	}
}

static int	file_error(char *str, int main)
{
	char	err[3];
	int		i;

	i = -1;
	while ((str[++i] == '<' || str[i] == '>'))
		err[i] = str[i];
	err[i] = '\0';
	ft_exit(ERR_TOKEN, err, main, 258);
	return (0);
}

static int	check_multifile(t_cmd_args *list, int main)
{
	int	n;
	int	i;

	n = 0;
	while (list)
	{
		if (list->arg[0])
		{
			i = -1;
			if (n && (list->arg[0] == '<' || list->arg[0] == '>'))
				return (file_error(list->arg, main));
			while ((list->arg[++i] == '<' || list->arg[i] == '>'))
				n++;
			if (n && list->arg[i])
				n = 0;
		}
		list = list->next;
	}
	return (1);
}

void	parse_files(t_data *data, t_cmd_args **list, int main)
{
	t_cmd_args	*node;

	node = NULL;
	if (check_multifile(*list, main))
	{
		p_file(data, list, &node, main);
		*list = node;
		while (*list && (*list)->prev)
			*list = (*list)->prev;
	}
}
