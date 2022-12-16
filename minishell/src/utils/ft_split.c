/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 18:49:26 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 18:49:28 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_char(char c, char *charset)
{
	int	i;

	i = -1;
	while (charset[++i] != '\0')
		if (charset[i] == c)
			return (0);
	return (1);
}

static int	ft_wordlen(const char *s, char *charset)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (ft_check_char(s[i], charset) && s[i])
	{
		i++;
		j++;
	}
	return (j);
}

static int	ft_msize(const char *s, char *charset)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (ft_check_char(s[i], charset))
			j++;
		while (s[i] && ft_check_char(s[i], charset))
			i++;
		while (s[i] && !ft_check_char(s[i], charset))
			i++;
	}
	return (j);
}

char	**ft_split(char const *s, char *charset)
{
	int		words;
	char	**str;
	int		i;

	i = 0;
	words = ft_msize(s, charset);
	str = malloc(8 * (words + 1));
	if (!str)
		return (NULL);
	str[words] = NULL;
	while (words--)
	{
		while (*s && !ft_check_char(*s, charset))
			s++;
		str[i] = ft_substr(s, 0, ft_wordlen(s, charset));
		if (!str[i])
			return (NULL);
		s = s + ft_wordlen(s, charset);
		i++;
	}
	return (str);
}
