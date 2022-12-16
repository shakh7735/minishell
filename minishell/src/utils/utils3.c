/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:15:54 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 19:17:59 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	i;

	if (!s)
		return (NULL);
	copy = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!copy)
		return (0);
	i = -1;
	while (s[++i])
		copy[i] = s[i];
	copy[i] = '\0';
	return (copy);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s && s[i])
		write(fd, &(s[i++]), 1);
}

static int	epur_len(char *str)
{
	int	i;
	int	len;

	if (!str)
		return (0);
	i = 0;
	len = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			++i;
		while (str[i] && str[i] != ' ' && str[i] != '\t')
			len += 1 + i++ *0;
		if (str[i])
			len++;
		else if (len > 0 && i > 0 && str[i - 1] == ' ')
			len--;
	}
	return (len);
}

char	*ft_epur_str(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*temp;

	len = epur_len(str);
	if (!len)
		return (NULL);
	temp = malloc(len + 1);
	j = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		++i;
	while (str[i])
	{
		if (j)
			temp[j++] = ' ';
		while (str[i] && str[i] != ' ' && str[i] != '\t')
			temp[j++] = str[i++];
		while (str[i] == ' ' || str[i] == '\t')
			++i;
	}
	temp[j] = '\0';
	return (temp);
}

void	ft_my_substr(char **s, unsigned int start, size_t len)
{
	char			*s1;
	int				i;
	unsigned int	size;
	unsigned int	m;

	if (!*s)
		return ;
	size = 0;
	while ((*s)[size])
		size++;
	if (size + 1 < start)
		m = 1;
	else if (size - start + 1 > len)
		m = len + 1;
	else
		m = size - start + 1;
	s1 = malloc(m);
	if (!s1)
		ft_exit(ERR_MALLOC, 0, 1, errno);
	i = -1;
	while (++i < (int)len && start + i < size && (*s)[i])
		s1[i] = (*s)[start + i];
	s1[i] = '\0';
	free(*s);
	*s = s1;
}
