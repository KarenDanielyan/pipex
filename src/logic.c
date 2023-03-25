/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:58:55 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/25 15:27:14 by kdaniely         ###   ########.fr       */
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

static void	check_command(char *path)
{
	if (!path)
	{
		errno = ENOENT;
		perror("check_command()");
		exit(EXIT_FAILURE);
	}
}

static void	bundle_init(struct s_bundle *bundle, int cmd_count)
{
	bundle->pipe_s = pipe_init(cmd_count - 1);
	bundle->pid_s = (int *)malloc(cmd_count * sizeof(int));
	if (!bundle->pid_s || !bundle->pipe_s)
	{
		perror("Malloc: ");
		exit(EXIT_FAILURE);
	}
	bundle->proc = NULL;
}

static void	execute_command(struct s_bundle bundle, char **envp,
						int cmd_count, int i)
{
	if (i == 0)
	{
		dup2(bundle.pipe_s[i].out, STDOUT_FILENO);
	}
	else if (i == (cmd_count - 1))
		dup2(bundle.pipe_s[i - 1].in, STDIN_FILENO);
	else
	{
		dup2(bundle.pipe_s[i - 1].in, STDIN_FILENO);
		dup2(bundle.pipe_s[i].out, STDOUT_FILENO);
	}
	pipe_close(bundle.pipe_s, (cmd_count - 1));
	exit(execve(bundle.proc->path, bundle.proc->cmd, envp));
}

void	parse(int ac, char **av)
{
	if (ac != 5)
	{
		ft_putstr_fd("Pipex: ", STDERR_FILENO);
		if (ac < 5)
			ft_putendl_fd("Insufficient number of agruments.", STDERR_FILENO);
		if (ac > 5)
			ft_putendl_fd(strerror(E2BIG), STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	redirect_io(ac, av);
}

void	loop(int cmd_count, char **av, char **envp, char **path)
{
	int				i;
	struct s_bundle	bundle;

	i = 0;
	bundle_init(&bundle, cmd_count);
	while (i < cmd_count)
	{
		bundle.proc = get_process(path, *(av + i));
		bundle.pid_s[i] = fork();
		if (bundle.pid_s[i] == -1)
		{
			perror("Fork");
			pipe_close(bundle.pipe_s, (cmd_count - 1));
			exit(EXIT_FAILURE);
		}
		else if (bundle.pid_s[i] == 0)
		{
			check_command(bundle.proc->path);
			execute_command(bundle, envp, cmd_count, i);
		}
		i ++;
		proc_free(bundle.proc);
	}
	pipe_close(bundle.pipe_s, (cmd_count - 1));
	while (wait(NULL) != -1)
		;
	free(bundle.pid_s);
	free(bundle.pipe_s);
}
