/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:58:55 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/21 22:22:11 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "pipex.h"

void	free_2d(char **ptr)
{
	int	i;

	i = 0;
	while (*(ptr + i))
	{
		free(*(ptr + i));
		i ++;
	}
	free(ptr);
}

#ifndef BONUS
void	parse(int ac, char **av)
{
	if (ac != 5)
	{
		ft_putstr_fd("Pipex: ", STDERR_FILENO);
		if (ac < 5)
			ft_putstr_fd("Insufficient number of agruments.", STDERR_FILENO);
		if (ac > 5)
			ft_putstr_fd(strerror(E2BIG), STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	redirect_io(ac, av);
}

#else
void	parse(int ac, char **av)
{
	if (ac < 5)
	{
		ft_putstr_fd("Pipex: Insufficient number of agruments.", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	redirect_io(ac, av);
}
#endif