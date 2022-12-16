/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 18:50:27 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 18:57:20 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_signals(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		printf("  \n");
		rl_on_new_line();
		rl_redisplay();
	}
	signal(SIGINT, handler_signals);
	signal(SIGQUIT, SIG_IGN);
}

void	handler_signals2(int sig)
{
	if (sig == SIGINT)
	{
		g_heredoc_sig = 0;
		rl_on_new_line();
		rl_redisplay();
		write(1, "  ", 2);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	}
	signal(SIGINT, handler_signals);
	signal(SIGQUIT, SIG_IGN);
}

void	handler_signals3(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
	}
	else if (sig == SIGQUIT)
		write(1, "Quit: 3\n", 8);
	signal(SIGINT, handler_signals);
	signal(SIGQUIT, SIG_IGN);
}
