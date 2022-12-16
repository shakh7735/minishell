/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 18:49:47 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 18:49:48 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_prog(t_data *data)
{
	clear_history();
	free_env(data->path);
	free(data->prog_path);
	free_list(&data->env);
	printf("exit\n");
	exit (errno);
}

static void	minishell(t_data *data)
{
	char	*line;

	while (1)
	{	
		data->fd_out = 0;
		data->fd_in = 0;
		chenge_vol_list(data, "?", ft_itoa(errno), 0);
		handler_signals(0);
		line = readline("super_power_shell-1.18$ ");
		if (!line && printf("exit\n"))
			exit(127);
		signal(SIGINT, handler_signals3);
		if (*line)
		{
			if (!get_multiline(&line, 0, 0))
				if (pipex_bonus(data, line))
					break ;
			add_history(line);
		}
		free (line);
	}
}

static void	init_data(t_data *data, char **envp, char *prog_name)
{
	init_ft_env(data, envp);
	data->prog_path = getcwd(0, 0);
	ft_my_strjoin(&data->prog_path, &prog_name[1]);
	data->cmd_args = NULL;
	errno = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data[1];

	(void)argc;
	init_data(data, envp, argv[0]);
	minishell(data);
	exit_prog(data);
	return (0);
}
