/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 03:08:11 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 03:09:57 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	list_tab_count(t_cmd_args *list)
{
	t_cmd_args	*temp;
	int			i;

	temp = list;
	i = 0;
	while (temp)
	{
		if (temp->arg[0] && temp->flag != 'd')
			i++;
		temp = temp->next;
	}
	return (i);
}

static void	list_to_args_make(t_cmd_args *list, char **args, int *i)
{
	while (list)
	{
		if (list->arg[0] && list->flag != 'd')
		{
			args[*i] = malloc(sizeof(char) * 1);
			if (!args[*i])
				ft_exit(ERR_MALLOC, 0, 1, errno);
			args[*i][0] = 0;
			while (list && list->arg[0] && list->flag != 'd')
			{
				ft_my_strjoin(&args[*i], list->arg);
				list = list->next;
			}
			*i += 1;
		}
		else
			list = list->next;
	}
}

char	**list_to_args(t_cmd_args *list)
{
	char	**args;
	int		i;

	args = (char **) malloc(sizeof(char *) * (list_tab_count(list) + 1));
	if (!args)
		ft_exit(ERR_MALLOC, 0, 1, errno);
	i = 0;
	list_to_args_make(list, args, &i);
	if (i)
		args[i] = NULL;
	else
	{
		free(args);
		args = NULL;
	}
	return (args);
}
