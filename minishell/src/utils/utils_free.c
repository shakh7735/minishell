/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:18:46 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 19:18:58 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(char **env)
{
	int	i;

	i = 0;
	if (env)
	{
		while (env[i])
			free(env[i++]);
		free (env);
	}
}

void	free_mtx(char **buff)
{
	int	i;

	i = -1;
	while (buff[++i])
		free(buff[i]);
	free(buff);
}
