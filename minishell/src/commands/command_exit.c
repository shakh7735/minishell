/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:05:33 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/31 22:05:45 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_my_atoi(char *str)
{
	int			i;
	int			n;
	long int	num;

	n = 1;
	num = 0;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == ' ' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			n = -n;
	while (str[i])
	{
		if (str[i] < '0' || '9' < str[i])
			ft_exit(ERR_EXIT_DIGIT, str, 1, 255);
		else
			num = num * 10 + str[i] - 48;
		if ((num > INT_MAX) || (-num < INT_MIN))
			ft_exit(ERR_EXIT_DIGIT, str, 1, 255);
		i++;
	}
	return (num * n);
}

void	command_exit(t_data *data)
{
	int	i;
	int	num;

	if (!ft_strcmp("exit", data->cmd_args[0]))
	{
		write(2, "exit\n", 5);
		i = -1;
		if (data->cmd_args[1])
			num = ft_my_atoi(data->cmd_args[1]);
		if (data->cmd_args[1] && data->cmd_args[2])
		{
			ft_exit(ERR_EXIT_ARG, 0, 0, 1);
			return ;
		}
		else if (data->cmd_args[1])
			exit(num);
		else
			exit(0);
	}
}
