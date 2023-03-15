/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:11:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/15 19:53:07 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <libft.h>
#include <fcntl.h>
#include "parse.h"
#include "pipex.h"

static void	redirect_io(int ac, char **av)
{
	int	fd[2];
	
	fd[0] = open(av[1], O_RDONLY | O_CREAT, 0700);
	fd[1] = open(av[ac - 1], O_WRONLY | O_CREAT, 0700);
	if (fd[0] == -1 || fd[1] == -1)
	{
		perror("Open: ");
		exit(EXIT_FAILURE);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}

int	main(int ac, char **av, char **envp)
{
	char	**path;
	t_pipe	pipe;
	int		pid;
	
	path = get_path(envp);
	redirect_io(ac, av);
	
	pipe = get_pipe();
	pid = fork();
	if (pid)
	{
		close(pipe.out);
		close(pipe.in);
		wait(NULL);
	}
	else
	{
		char	**cmd = ft_split(av[2], ' ');
		execve(get_file_path(path, cmd[0]), cmd, envp);
	}
	return (0);
}