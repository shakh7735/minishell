/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:14:56 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 19:15:18 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

void	ft_my_strjoin(char **s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *)malloc(ft_strlen(*s1) + ft_strlen(s2) + 1);
	if (!str)
		return ;
	i = 0;
	while (i < ft_strlen(*s1))
	{
		str[i] = (*s1)[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
		str[i++] = s2[j++];
	str[i] = '\0';
	free(*s1);
	*s1 = str;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*s1;
	size_t			i;
	unsigned int	size;
	unsigned int	m;

	if (!s)
		return (NULL);
	size = 0;
	while (s[size])
		size++;
	if (size + 1 < start)
		m = 1;
	else if (size - start + 1 > len)
		m = len + 1;
	else
		m = size - start + 1;
	s1 = malloc(m);
	if (!s1)
		return (NULL);
	i = -1;
	while (++i < len && start + i < size && s[i])
		s1[i] = s[start + i];
	s1[i] = '\0';
	return (s1);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*ds;
	char	*sr;

	ds = dst;
	sr = (char *)src;
	if (sr < ds)
	{
		while (len--)
			*(ds + len) = *(sr + len);
	}
	else
		while (len--)
			*ds++ = *sr++;
	return (dst);
}

char	*str_to_lowercase(char *s)
{
	char	*r;
	int		i;

	if (!s)
		return (NULL);
	i = -1;
	while (s[++i])
		if (s[i] < 'A' || s[i] > 'Z')
			return (ft_strdup(s));
	r = malloc(sizeof(char) * (i + 2));
	i = -1;
	while (s[++i])
		r[i] = s[i] + 32;
	r[i] = 0;
	return (r);
}
