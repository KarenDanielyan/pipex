/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:15:09 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/25 17:39:00 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "parse.h"
#include <fcntl.h>

t_pipe	*pipe_init(int len)
{
	int		i;
	t_pipe	*pipe_s;

	i = 0;
	pipe_s = (t_pipe *)malloc(len * sizeof(t_pipe));
	if (!pipe_s)
	{
		perror("Malloc: ");
		exit(EXIT_FAILURE);
	}
	while (i < len)
	{
		pipe_s[i] = get_pipe();
		i ++;
	}
	return (pipe_s);
}

t_pipe	get_pipe(void)
{
	int		fd[2];
	t_pipe	pip;

	if (pipe(fd) == -1)
	{
		perror("pipe: ");
		exit(EXIT_FAILURE);
	}
	pip.in = fd[0];
	pip.out = fd[1];
	return (pip);
}

void	pipe_close(t_pipe	*p_arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		close((p_arr + i)->in);
		close((p_arr + i)->out);
		i ++;
	}
}

t_pipe	redirect_io(int ac, char **av)
{
	t_pipe	pip;
	int	fd[2];

	fd[0] = open(av[1], O_RDONLY);
	fd[1] = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0600);
	if (fd[0] == -1 || fd[1] == -1)
		perror("Open: ");
	pip.in = fd[0];
	pip.out = fd[1];
	return (pip);
}
