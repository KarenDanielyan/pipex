/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:44:19 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/23 21:39:03 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "parse.h"
#include <fcntl.h>

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

void	execute_command(char **cmd, char *path, char **envp)
{
	t_pipe	pipe;
	int		pid;

	pipe = get_pipe();
	pid = fork();
	if (pid)
	{
		close(pipe.out);
		dup2(pipe.in, STDIN_FILENO);
		close(pipe.in);
		wait(NULL);
	}
	else
	{
		close(pipe.in);
		dup2(pipe.out, STDOUT_FILENO);
		close(pipe.out);
		exit(execve(path, cmd, envp));
	}
}

void	loop(int ac, char **av, char **envp, char **path)
{
	int			i;
	int			pid;
	t_process	proc;

	if (get_type(*(av + 1), path) == HDOC)
		i = 3;
	else
		i = 2;
	while (i < (ac - 1))
	{
		proc = get_process(path, av[i]);
		if (i < (ac - 2))
			execute_command(proc.cmd, proc.path, envp);
		else
		{
			pid = fork();
			if (!pid)
				exit(execve(proc.path, proc.cmd, envp));
		}
		proc_zero(&proc);
		i ++;
	}
}

void	redirect_io(int ac, char **av, char **path)
{
	int	fd[2];

	if (get_type(*(av + 1), path) == HDOC)
	{
		fd[0] = open(HDOC_FILE, O_RDONLY);
		fd[1] = open(*(av + ac -1), O_WRONLY | O_APPEND | O_CREAT, 0600);
	}
	else
	{
		fd[0] = open(*(av + 1), O_RDONLY);
		fd[1] = open(*(av + ac -1), O_WRONLY | O_CREAT, 0600);
	}
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
