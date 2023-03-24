/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:11:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/24 20:27:58 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "pipex.h"


void	pipe_init(t_pipe *p_arr, int len)
{
	int	i;
	int	fd[2];

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
/*	char		**av;
	t_pipe		*pip_arr;
	int			*pid_arr;
	t_process	proc;
	int			i;

	pip_arr = (t_pipe *)malloc((ac - 2) * sizeof(t_pipe));
	pid_arr = (int *)malloc((ac - 1) * sizeof(int));
	pipe_init(pip_arr, ac - 2);
	path = get_path(envp);
	av = argv;
	av ++;
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
*/
	path = get_path(envp);
	loop(ac, (av + 1), envp, path);
	free_2d(path);
	return (0);
}
