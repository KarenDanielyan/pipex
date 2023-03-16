/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:11:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/16 18:10:13 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <libft.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
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

static void	execute_command(char **cmd, char *path, char **envp)
{
	t_pipe	pipe;
	int		pid;
	int		status;

	pipe = get_pipe();
	pid = fork();
	if (pid)
	{
		close(pipe.out);
		dup2(pipe.in, STDIN_FILENO);
		close(pipe.in);
		wait(&status);
		if (status == 1)
		{
			ft_printf("Execve: %s\n", strerror(status));
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		close(pipe.in);
		dup2(pipe.out, STDOUT_FILENO);
		close(pipe.out);
		exit(execve(path, cmd, envp));
	}
}

static void	loop(int ac, char **av, char **envp, char **path)
{
	int		i;
	int		pid;
	t_process	proc;

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

int	main(int ac, char **av, char **envp)
{
	char	**path;
	int		pid;
	
	path = get_path(envp);
	redirect_io(ac, av);
	loop(ac, av, envp, path);
	free_2d(path);	
	/*
	t_pipe	pipe = get_pipe();
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
	}*/
	return (0);
}