/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:41:25 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/16 21:01:19 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <libft.h>
#include "pipex.h"
#include "parse.h"

char	*get_file_path(char **path, char *file)
{
	char	*file_w_slash;
	char	*join;

	if (access(file, X_OK) == 0)
		return (ft_strdup(file));
	if (file[0] != '/')
		file_w_slash = ft_strjoin("/", file);
	else
		file_w_slash = file;
	while (path)
	{
		join = ft_strjoin(*path, file_w_slash);
		if (access(join, X_OK) == 0 || !join)
			break ;
		path ++;
		free(join);
		join = NULL;
	}
	if (file[0] != '/')
		free(file_w_slash);
	return (join);
}

char	**get_path(char **envp)
{
	char	*path;
	char	**split;
	int		i;

	i = 0;
	path = NULL;
	while (*(envp + i))
	{
		if (ft_strncmp(*(envp + i), "PATH=", 5) == 0)
		{
			path = *(envp + i);
			break ;
		}
		i ++;
	}
	if (path == NULL)
	{
		ft_printf("Error: no PATH variable in env!!\n");
		system("leaks pipex");
		exit(EXIT_FAILURE);
	}
	path = ft_strtrim(path, "PATH=");
	split = ft_split(path, ':');
	free(path);
	return (split);
}

void	free_2d(char **ptr)
{
	int	i;

	i = 0;
	while (*(ptr + i))
	{
		free(*(ptr + i));
		i ++;
	}
	free(ptr);
}

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
		system("leaks pipex");
		exit(EXIT_FAILURE);
	}
	path_to = get_file_path(path, cmd[0]);
	if (!path_to)
	{
		perror("Access: ");
		system("leaks pipex");
		exit(EXIT_FAILURE);
	}
	process.cmd = cmd;
	process.path = path_to;
	return (process);
}
