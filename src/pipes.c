/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:15:09 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/24 20:27:43 by kdaniely         ###   ########.fr       */
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

void	redirect_io(int ac, char **av)
{
	int	fd[2];

	fd[0] = open(av[1], O_RDONLY);
	fd[1] = open(av[ac - 1], O_WRONLY | O_CREAT, 0600);
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
	t_pipe		*pip_arr;
	int			*pid_arr;
	t_process	proc;
	int			i;

	pip_arr = (t_pipe *)malloc((ac - 2) * sizeof(t_pipe));
	pid_arr = (int *)malloc((ac - 1) * sizeof(int));
	pipe_init(pip_arr, ac - 2);
	i = 0;
	while (i < ac - 1)
	{
		proc = get_process(path, *(av + i));
		pid_arr[i] = fork();
		if (pid_arr[i] == 0)
		{
			if (i == 0)
				dup2(pip_arr[i].out, STDOUT_FILENO);
			else if (i == (ac - 2))
				dup2(pip_arr[i - 1].in, STDIN_FILENO);
			else
			{
				dup2(pip_arr[i - 1].in, STDIN_FILENO);
				dup2(pip_arr[i].out, STDOUT_FILENO);
			}
			pipe_close(pip_arr, ac - 2);
			exit(execve(proc.path, proc.cmd, envp));
		}
		i ++;
		proc_zero(&proc);
	}
	pipe_close(pip_arr, ac - 1);
	while(wait(NULL) != -1)
		;
	free(pip_arr);
	free(pid_arr);
}

