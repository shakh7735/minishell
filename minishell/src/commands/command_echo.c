/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 22:52:18 by akazarya          #+#    #+#             */
/*   Updated: 2022/08/04 22:52:19 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_minus(char *str)
{
	int	i;

	i = 0;
	while (str[++i])
		if (str[i] == '-')
			return (0);
	return (1);
}

void	command_echo(t_data *data)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (data->cmd_args[++i])
	{
		if (data->cmd_args[i][0] == '-' && check_minus(data->cmd_args[i]))
		{
			if (data->cmd_args[i][1] == 'n')
			{
				flag = 0;
				continue ;
			}
		}
		ft_putstr_fd(data->cmd_args[i], 1);
		if (data->cmd_args[i + 1])
			write(1, " ", 1);
	}
	if (flag)
		write(1, "\n", 1);
}
