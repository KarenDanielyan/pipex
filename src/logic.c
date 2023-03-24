/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:58:55 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/24 21:31:13 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "pipex.h"

struct	s_bundle
{
	int			*pid_s;
	t_pipe		*pipe_s;
	t_process	*proc;
};

static void	bundle_init(struct s_bundle *bundle, int ac)
{
	int			*pid_s;
	t_pipe		*pipe_s;

	pid_s = (int *)malloc((ac - 1) * sizeof(int));
	pipe_s = pipe_init(ac - 2);
	if (!pid_s || !pipe_s)
	{
		perror("Malloc: ");
		exit(EXIT_FAILURE);
	}
	bundle->pid_s = pid_s;
	bundle->pipe_s = pipe_s;
	bundle->proc = NULL;
}

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

static void	execute_command(struct s_bundle bundle, char **envp, int ac, int i)
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

	i = 0;
	bundle_init(&bundle, ac);
	while (i < ac - 3)
	{
		bundle.proc = get_process(path, *(av + i + 1));
		bundle.pid_s[i] = fork();
		if (bundle.pid_s[i] == 0)
			execute_command(bundle, envp, ac - 2, i);
		i ++;
		proc_zero(bundle.proc);
	}
	pipe_close(bundle.pipe_s, ac - 1);
	while(wait(NULL) != -1)
		;
	free(bundle.pid_s);
	free(bundle.pipe_s);
}
