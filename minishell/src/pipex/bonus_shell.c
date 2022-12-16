/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 03:29:45 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/31 22:12:25 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_parient_arg(char **arg, int *par)
{
	int	i;

	i = -1;
	while ((*arg)[++i])
	{
		if (!i && (*arg)[i] == '(')
		{
			ft_my_substr(arg, i + 1, ft_strlen(*arg) - i);
			*par = 1;
		}
		else if (!(*arg)[i + 1] && (*arg)[i] == ')')
		{
			ft_my_substr(arg, 0, i);
			*par = 3;
		}
	}
}

static void	check_parient(t_cmd_args **list)
{
	t_cmd_args	*elem;
	int			par;

	par = 0;
	elem = *list;
	while (elem)
	{
		ft_my_strtrim(&elem->arg, " \t");
		if (par == 1)
			par = 2;
		check_parient_arg(&elem->arg, &par);
		elem->flag_par = par;
		if (par == 3)
		{
			elem->flag_par = 2;
			par = 0;
		}
		elem = elem->next;
	}
}

static void	create_new_elem_and_or_list(t_cmd_args **elem, char *s, int *j)
{
	int	i;
	int	k;
	int	flag_par;

	i = j[0];
	k = j[1];
	flag_par = j[2];
	new_list_arg(elem, NULL);
	(*elem)->flag = flag_par;
	(*elem)->arg = ft_substr(s, k, i - k);
	if (s[i] == '&' && s[i + 1] == '&')
		flag_par = 1;
	else if (s[i] == '|' && s[i + 1] == '|')
		flag_par = 0;
	if (!(*elem)->prev)
		(*elem)->flag = 1;
	k = 2 + i++;
	j[0] = i;
	j[1] = k;
	j[2] = flag_par;
}

static t_cmd_args	*make_and_or_list(char *s)
{
	int			i[3];
	t_cmd_args	*elem;

	i[0] = -1;
	i[1] = 0;
	i[2] = 0;
	elem = NULL;
	while (s[++i[0]])
	{
		if (s[i[0] + 1] && ((s[i[0] + 1] == '&' && s[i[0]] == '&')
				|| (s[i[0] + 1] == '|' && s[i[0]] == '|')))
			create_new_elem_and_or_list(&elem, s, i);
	}
	create_new_elem_and_or_list(&elem, s, i);
	while (elem->prev)
		elem = elem->prev;
	check_parient(&elem);
	return (elem);
}

int	pipex_bonus(t_data *data, char *line)
{
	t_cmd_args	*args;

	signal(SIGQUIT, handler_signals3);
	args = make_and_or_list(line);
	while (args && args->arg[0])
	{
		if ((!args->flag && errno) || (args->flag == 1 && !errno))
			pipex(data, args->arg);
		else if (args->flag_par == 1)
			while (args->next && args->next->flag_par == 2)
					args = args->next;
		if (args->next)
			args = args->next;
		else
			break ;
	}
	free_list_cmd_args(args);
	return (0);
}
