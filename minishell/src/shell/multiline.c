/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 03:10:12 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 03:10:48 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_count(char *str)
{
	int		pipe_count;
	char	c;
	int		i;

	pipe_count = 1;
	i = 1;
	c = 0;
	while (str[i])
	{
		while (str[i] && !c)
		{
			if (str[i] == '\'' || str[i] == '\"')
				c = str[i++];
			else if (str[i++] == '|' && str[i])
				pipe_count++;
		}
		while (str[i] && str[i] != c)
			i++;
		if (str[i])
			c = 0 * i++;
	}
	return (pipe_count);
}

static int	check_quote(char *str, int i, int pipe_count, char c)
{
	while (str[i])
	{
		while (str[i] && !c)
		{
			if (str[i] == '\'' || str[i] == '\"')
				c = str[i++];
			else if (str[i++] == '|' && str[i])
				pipe_count++;
		}
		while (str[i] && str[i] != c)
			i++;
		if (str[i])
			c = 0 * i++;
	}
	if (!c && str[i - 1] != '|')
		return (0);
	while (pipe_count--)
		printf("pipe ");
	str[i] = '\n';
	str[i + 1] = '\0';
	if (c)
		return (1);
	return (2);
}

static int	check_multiline(char *line, int id)
{
	if (!g_heredoc_sig)
		return (1);
	if (check_quote(line, 0, 0, 0) == 1)
		ft_exit(ERR_EOF1, 0, 0, 0);
	if (id)
		ft_exit(ERR_EOF2, 0, 0, 258);
	return (id);
}

void	my_free(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

int	get_multiline(char **line, int id, char *str)
{
	g_heredoc_sig = 1;
	signal(SIGINT, handler_signals2);
	while (g_heredoc_sig)
	{
		str = NULL;
		id = check_quote(*line, 0, 0, 0);
		if (id == 1)
			str = readline("quote> ");
		else if (id == 2)
		{
			while (g_heredoc_sig && (!str || !str[0]))
			{
				str = readline("pipe> ");
				if (str && !str[0])
					my_free(&str);
				else
					break ;
			}
		}
		if (!id || !str)
			break ;
		ft_my_strjoin(line, str);
		my_free(&str);
	}
	return (check_multiline(*line, id));
}
