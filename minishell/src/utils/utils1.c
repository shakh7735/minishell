/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:14:39 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 19:14:40 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char *err, char *cmd, int id, int ercode)
{
	write(2, err, ft_strlen(err));
	if (cmd)
		write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	errno = ercode;
	if (id)
		exit(errno);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
		if (*s++ == (unsigned char)c)
			return ((char *)s - 1);
	if (!c && !*s)
		return ((char *)s);
	return (NULL);
}

int	ft_my_strchr(const char *s, int c)
{
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] == (unsigned char)c)
			return (i + 1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
		{
			n = s1[i] - s2[i];
			break ;
		}
		i++;
	}
	return (n);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
