/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:15:09 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/25 00:15:14 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "parse.h"
#include <fcntl.h>

struct	s_bundle
{
	int			*pid_s;
	t_pipe		*pipe_s;
	t_process	*proc;
};

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

void	execute_command(struct s_bundle bundle, char **envp, int ac, int i)
{
	if (i == 0)
		dup2(bundle.pipe_s[i].out, STDOUT_FILENO);
	else if (i == (ac - 2))
		dup2(bundle.pipe_s[i - 1].in, STDIN_FILENO);
	else
	{
		dup2(bundle.pipe_s[i - 1].in, STDIN_FILENO);
		dup2(bundle.pipe_s[i].out, STDOUT_FILENO);
	}
	pipe_close(bundle.pipe_s, ac - 2);
	exit(execve(bundle.proc->path, bundle.proc->cmd, envp));
}

void	loop(int ac, char **av, char **envp, char **path)
{
	int				i;
	struct s_bundle	bundle;

	bundle.pipe_s = (t_pipe *)malloc((ac - 2) * sizeof(t_pipe));
	bundle.pid_s = (int *)malloc((ac - 1) * sizeof(int));
	pipe_init(bundle.pipe_s, ac - 2);
	i = 0;
	while (i < ac - 1)
	{
		bundle.proc = get_process(path, *(av + i));
		bundle.pid_s[i] = fork();
		if (bundle.pid_s[i] == 0)
			execute_command(bundle, envp, ac, i);
		i ++;
		proc_zero(bundle.proc);
	}
	pipe_close(bundle.pipe_s, ac - 1);
	while(wait(NULL) != -1)
		;
	free(bundle.pid_s);
	free(bundle.pipe_s);
}
