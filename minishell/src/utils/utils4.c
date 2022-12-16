/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:25:16 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/31 22:13:00 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_str_short_begin(char **str, int start)
{
	char	*new;

	new = ft_substr(*str, start, ft_strlen(*str) - start);
	free(*str);
	*str = new;
}

char	**ft_split_equal(char *s)
{
	int		i;
	char	**t;

	t = (char **)malloc(sizeof(char *) * 3);
	if (!t)
		ft_exit (ERR_MALLOC, 0, 1, errno);
	i = -1;
	while (s[++i])
		if (s[i] == '=')
			break ;
	t[0] = ft_substr(s, 0, i);
	if (s[i] == '=')
		t[1] = ft_substr(s, i + 1, ft_strlen(s) - i);
	else
		t[1] = NULL;
	t[2] = NULL;
	return (t);
}

int	is_my_alpha(char c)
{
	if ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| c == '_')
		return (1);
	return (0);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	get_errno(int ret)
{
	if (WIFEXITED(ret))
		errno = WEXITSTATUS(ret);
}
