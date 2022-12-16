/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 18:49:06 by akazarya          #+#    #+#             */
/*   Updated: 2022/07/29 18:49:08 by akazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_nbr_size(int n)
{
	unsigned int	x;
	int				size;

	size = 0;
	x = n;
	if (n < 0)
	{
		size++;
		x = -n;
	}
	else if (n == 0)
		size++;
	while (x > 0)
	{
		x = x / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	unsigned int	x;
	int				size;
	char			*str_rez;

	size = ft_nbr_size(n);
	str_rez = (char *)malloc(size + 1);
	if (!str_rez)
		return (NULL);
	x = n;
	if (n < 0)
	{
		str_rez[0] = '-';
		x = -n;
	}
	while ((size > 1 && n < 0) || (size >= 1 && n >= 0))
	{
		str_rez[size - 1] = (x % 10 + 48);
		x = x / 10;
		size--;
	}
	str_rez[ft_nbr_size(n)] = '\0';
	return (str_rez);
}
