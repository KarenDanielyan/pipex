/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:42:00 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/23 21:39:35 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "parse.h"

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
		exit(EXIT_FAILURE);
	}
	path = ft_strtrim(path, "PATH=");
	split = ft_split(path, ':');
	free(path);
	return (split);
}

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

t_type	get_type(char *av, char **path)
{
	char	*file;

	file = get_file_path(path, av);
	if (file == NULL)
	{
		if (access(av, F_OK) == 0)
			return (FIL);
		else if (ft_strcmp(av, "here_doc") == 0)
			return (HDOC);
		else
			return (NVA);
	}
	else
	{
		free(file);
		return (CMD);
	}
}