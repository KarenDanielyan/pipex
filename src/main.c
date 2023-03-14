/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:11:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/14 22:34:05 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <libft.h>
#include <fcntl.h>
#include "parse.h"
#include "pipex.h"

/*static void	check_input(int ac, char **av)
{
	if (ac < 5 && !BONUS)
	{
		ft_printf("Insufficient number of arguments.\n");
		exit(EXIT_FAILURE);
	}
	if (get_arg_type(av[0]) == FIL && get_arg_type(av[ac - 1]) == FIL)
	{
		if (access(av[0], F_OK) == -1 || access(av[ac - 1], F_OK) == -1)
		{
			perror("Access: ");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		ft_printf("First and last arguments are not files!!!\n");
		exit(EXIT_FAILURE);
	}
}*/

static void	redirect_io(int ac, char **av)
{
	int	fd[2];
	
	fd[0] = open(av[1], O_RDONLY);
	fd[1] = open(av[ac - 1], O_WRONLY);
	if (fd[0] == -1 || fd[1] == -1)
	{
		perror("Open: ");
		exit(EXIT_FAILURE);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
}

static void	execute_pipe(char **cmd, char *path, char **envp)
{
	int		pid;
	t_pipe	pipe;

	pipe = get_pipe();
	pid = fork();
	if (pid)
	{
		close(pipe.out);
		dup2(pipe.in, STDIN_FILENO);
		wait(NULL);
	}
	else
	{
		close(pipe.in);
		dup2(pipe.out, STDOUT_FILENO);
		if (execve(path, cmd, envp) == -1)
		{
			perror("execve: ");
			exit(EXIT_FAILURE);
		}
		else
			exit(EXIT_SUCCESS);
	}
}

static void	loop(int ac, char **av, char **envp, char **path)
{
	int	i;
	char	**cmd;
	char	*bin_path;

	i = 2;
	while (i < (ac - 1))
	{
		cmd = ft_split(*(av + i), ' ');
		bin_path = get_file_path(path, *cmd);
		execute_pipe(cmd, bin_path, envp);
		i ++;
		free(bin_path);
		free(cmd);		//TODO: Add 2d split
	}
}

int	main(int ac, char **av, char **envp)
{
	char	**path;

	path = get_path(envp);
	redirect_io(ac, av);
	execute_pipe(ft_split("wc -l", ' '), "/usr/bin/wc", envp);
	//loop(ac, av, envp, path);
	return (0);
}