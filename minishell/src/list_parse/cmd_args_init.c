/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 03:33:05 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 03:47:50 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_list_quote(char *line, t_cmd_args *list, int i)
{
	char	c;

	while (*line)
	{
		i = 0;
		while (*(line + i) && *(line + i) != '\'' && *(line + i) != '\"')
			i++;
		c = *(line + i);
		if (i)
		{
			list->arg = ft_substr(line, 0, i);
			line += i;
			if (!*line)
				break ;
			new_list_add(&list);
		}
		i = 1;
		while (*(line + i) && *(line + i) != c)
			i++;
		list->arg = ft_substr(line, 1, i - 1);
		list->flag = *line;
		line += i + 1;
		if (*line)
			new_list_add(&list);
	}
}

static void	split_list_space_make(t_cmd_args *list, char **temp, char *p)
{
	int		i;

	i = -1;
	if (p[0] == ' ' && list->prev)
	{
		list->arg = ft_strdup("");
		new_list_arg(&list, temp[++i]);
	}
	else
		list->arg = ft_strdup(temp[++i]);
	while (temp[++i])
	{
		new_list_arg(&list, "");
		new_list_arg(&list, temp[i]);
	}
	if (p[ft_strlen(p) - 1] == ' ' && list->next)
		new_list_arg(&list, "");
}

static void	split_list_space(t_cmd_args *list)
{
	char	**temp;
	char	*p;

	while (list)
	{
		if (!list->flag)
		{
			temp = ft_split(list->arg, " \t\n");
			p = list->arg;
			if (temp[0])
				split_list_space_make(list, temp, p);
			else
				list->arg = ft_strdup("");
			free_env(temp);
			free(p);
		}
		list = list->next;
	}
}

static void	split_list_redirections(t_cmd_args *list, int i)
{
	char	*p;

	while (list)
	{
		i = -1;
		if (!list->flag && list->arg[++i])
		{
			while (list->arg[i + 1]
				&& (list->arg[i + 1] != '<' || (list->arg[i] == '<' && !(i)))
				&& (list->arg[i + 1] != '>' || (list->arg[i] == '>' && !(i))))
				i++;
			if (list->arg[++i])
			{
				p = list->arg;
				list->arg = ft_substr(list->arg, 0, i);
				if (p[i])
					new_list_arg(&list, &(p[i]));
				else
					list = list->next;
				free(p);
				continue ;
			}
		}
		list = list->next;
	}
}

char	**init_cmd_to_list(t_data *data, char *line, int main)
{
	t_cmd_args	*cmd_args;
	char		**args;

	cmd_args = NULL;
	new_list_add(&cmd_args);
	split_list_quote(line, cmd_args, 0);
	split_list_space(cmd_args);
	check_make_dollar(data->env, cmd_args);
	equal_exist(data, &cmd_args, main);
	split_list_redirections(cmd_args, 0);
	parse_files(data, &cmd_args, main);
	args = list_to_args(cmd_args);
	free_list_cmd_args(cmd_args);
	return (args);
}
