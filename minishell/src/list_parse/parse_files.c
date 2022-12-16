/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 18:50:27 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 18:57:20 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_infile(t_data *data, char *infile, int main)
{
	if (data->fd_in)
		close(data->fd_in);
	data->fd_in = open(infile, O_RDONLY);
	if (!access(infile, F_OK) && data->fd_in == -1)
		ft_exit(ERR_PERMITION, infile, main, errno);
	else if (data->fd_in == -1)
		ft_exit(ERR_FILE, infile, main, errno);
}

static void	init_heredoc(t_data *data, char *limit, int main)
{
	int			fd_in;
	t_cmd_args	*list;

	fd_in = open(HEREDOC, O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (fd_in == -1)
		ft_exit(ERR_FILE, HEREDOC, main, errno);
	list = NULL;
	new_list_add(&list);
	while (g_heredoc_sig)
	{
		list->arg = readline("heredoc> ");
		if (!list->arg || !ft_strcmp(list->arg, limit))
			break ;
		check_make_dollar(data->env, list);
		write(fd_in, list->arg, ft_strlen(list->arg));
		write(fd_in, "\n", 1);
		free(list->arg);
	}
	free_list_cmd_args(list);
	close (fd_in);
	if (g_heredoc_sig)
		init_infile(data, HEREDOC, main);
	else
		data->fd_in = -1;
}

int	check_in_out(t_data *data, t_cmd_args *list, t_cmd_args **arg, int main)
{
	if (list->arg[0] == '<' && list->arg[1] == '<')
	{
		ft_str_short_begin(&list->arg, 2);
		g_heredoc_sig = 1;
		signal(SIGINT, handler_signals2);
		signal(SIGQUIT, SIG_IGN);
		init_heredoc(data, (*arg)->arg, main);
	}
	else if (list->arg[0] == '<')
	{
		ft_str_short_begin(&list->arg, 1);
		init_infile(data, (*arg)->arg, main);
	}
	else if (!check_in_out2(data, list, arg, main))
		return (0);
	if (list != *arg)
		delete_list_arg(&list);
	delete_list_arg(arg);
	return (1);
}
