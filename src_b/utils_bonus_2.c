/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:43:27 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/23 21:39:49 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "pipex.h"

void	proc_zero(t_process *proc)
{
	free(proc->path);
	free_2d(proc->cmd);
	proc->cmd = NULL;
	proc->path = NULL;
}

t_process	get_process(char **path, char *av)
{
	char		**cmd;
	char		*path_to;
	t_process	process;

	cmd = ft_split(av, ' ');
	if (!cmd)
	{
		perror("Malloc ");
		exit(EXIT_FAILURE);
	}
	path_to = get_file_path(path, cmd[0]);
	if (!path_to)
	{
		perror("Access: ");
		exit(EXIT_FAILURE);
	}
	process.cmd = cmd;
	process.path = path_to;
	return (process);
}
