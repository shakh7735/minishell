/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:10:30 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 19:12:30 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dollar_get_key(t_env *env, t_cmd_args *list, char *key, int *i)
{
	t_env	*elem;
	char	*temp;
	char	*vol;

	if (!key)
		return ;
	elem = list_env_search_key(env, key);
	temp = ft_substr(list->arg, *i + 1 + ft_strlen(key), ft_strlen(list->arg));
	ft_my_substr(&list->arg, 0, *i);
	if (elem)
	{
		if (list->flag)
			vol = ft_strdup(elem->vol);
		else
			vol = ft_epur_str(elem->vol);
	}
	else
		vol = ft_strdup("");
	ft_my_strjoin(&list->arg, vol);
	ft_my_strjoin(&list->arg, temp);
	free(temp);
	free(key);
	*i += ft_strlen(vol);
	free(vol);
}

static int	get_key_id(char *str)
{
	int	i;

	if (str[0] == '?')
		return (1);
	i = 0;
	while ((str[i] >= 'A' && str[i] <= 'Z')
		|| (str[i] >= 'a' && str[i] <= 'z')
		|| (str[i] >= '0' && str[i] <= '9')
		|| str[i] == '_')
			i++;
	return (i);
}

void	check_make_dollar(t_env *env, t_cmd_args *list)
{
	int		i;
	char	*arg;

	while (list)
	{
		if (list->flag != '\'')
		{
			i = 0;
			arg = list->arg;
			while (arg && ft_my_strchr(&arg[i], '$')
				&& arg[ft_my_strchr(arg, '$')])
			{
				i += ft_my_strchr(&arg[i], '$') - 1;
				if (!is_my_alpha(arg[i + 1]) && arg[i + 1] != '?')
					continue ;
				dollar_get_key(env, list,
					ft_substr(&arg[i + 1], 0, get_key_id(&arg[i + 1])), &i);
				arg = list->arg;
			}
			if (arg[i] == '$' && !arg[i + 1] && list->next \
				&& (list->next->flag == '\'' || list->next->flag == '\"'))
				ft_my_substr(&list->arg, 0, i);
		}
		list = list->next;
	}
}
