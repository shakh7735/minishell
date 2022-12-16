/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:23:10 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/31 22:23:13 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_beginsize(const char *s, char const *set)
{
	unsigned int	i;
	unsigned int	k;

	i = 0;
	k = 0;
	while (s[i] && set[k])
		if (s[i] == set[k++])
			k = 0 * i++;
	return (i);
}

static int	ft_endsize(const char *s, char const *set)
{
	unsigned int	i;
	unsigned int	k;

	i = ft_strlen(s);
	k = 0;
	while (i && set[k])
		if (s[i - 1] == set[k++])
			k = 0 * i--;
	return (ft_strlen(s) - i);
}

void	ft_my_strtrim(char **s1, char const *set)
{
	char	*str;
	int		size;
	int		begin;
	int		end;

	if (!*s1)
		return ;
	size = ft_strlen(*s1);
	begin = ft_beginsize(*s1, set);
	end = ft_endsize(*s1, set);
	if (size - begin - end > 0)
		str = ft_substr(*s1, begin, size - begin - end);
	else
		str = ft_substr(*s1, size, 1);
	if (*s1)
		free(*s1);
	*s1 = str;
}
