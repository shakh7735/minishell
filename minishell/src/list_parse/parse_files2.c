/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 18:50:27 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 18:57:20 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_outfile(t_data *data, char *outfile, int main)
{
	if (data->fd_out)
		close(data->fd_out);
	data->fd_out = open(outfile, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (!access(outfile, F_OK) && data->fd_out == -1)
		ft_exit(ERR_PERMITION, outfile, main, errno);
	else if (data->fd_out == -1)
		ft_exit(ERR_FILE, outfile, main, errno);
}

static void	init_outfile_append(t_data *data, char *outfile, int main)
{
	if (data->fd_out)
		close(data->fd_out);
	data->fd_out = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 0000644);
	if (!access(outfile, F_OK) && data->fd_out == -1)
		ft_exit(ERR_PERMITION, outfile, main, errno);
	else if (data->fd_out == -1)
		ft_exit(ERR_FILE, outfile, main, errno);
}

int	check_in_out2(t_data *data, t_cmd_args *list, t_cmd_args **arg, int main)
{
	if (list->arg[0] == '>' && list->arg[1] == '>')
	{
		ft_str_short_begin(&list->arg, 2);
		init_outfile_append(data, (*arg)->arg, main);
	}
	else if (list->arg[0] == '>')
	{
		ft_str_short_begin(&list->arg, 1);
		init_outfile(data, (*arg)->arg, main);
	}
	else
		return (0);
	return (1);
}
