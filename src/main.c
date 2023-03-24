/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:11:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/25 00:47:02 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "pipex.h"


void	pipe_init(t_pipe *p_arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		p_arr[i] = get_pipe();
		i ++;
	}
}

int	main(int ac, char **av, char **envp)
{
	char		**path;
	path = get_path(envp);
	redirect_io(ac, av);
	loop((ac - 3), (av + 2), envp, path);
	free_2d(path);
	return (0);
}
