/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:58:55 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/25 02:32:21 by kdaniely         ###   ########.fr       */
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

int	parse(int ac, char **av, char **path)
{
	int	rv;

	rv = 0;
	if (ac < 5)
	{
		ft_putstr_fd("Pipex: Insufficient number of agruments.", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (get_type(*(av + 1), path) == HDOC)
	{
		rv = 1;
		hdoc_checker(ac, av);
		hdoc_handler(*(av + 2));
	}
	redirect_io(ac, av, path);
	return (rv);
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
		if (bundle.pid_s[i] == 0)
			execute_command(bundle, envp, cmd_count, i);
		i ++;
		proc_free(bundle.proc);
	}
	pipe_close(bundle.pipe_s, (cmd_count - 1));
	while (wait(NULL) != -1)
		;
	free(bundle.pid_s);
	free(bundle.pipe_s);
}
