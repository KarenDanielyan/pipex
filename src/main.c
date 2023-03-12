/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:11:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/12 21:30:11 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <libft.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "parse.h"

static char	**get_path(char **envp)
{
	char	*path;
	char	**split;
	int		i;
	int		len;

	i = 0;
	while (*(envp + i))
	{
		if (ft_strncmp(*(envp + i), "PATH=", 5) == 0)
			break;
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

static	char	*get_exec(char **path, char *cmd)
{
	char	*join;

	while (path) 
	{
		join = ft_strjoin(*path, cmd);
		if (access(join, X_OK) == 0)
			return (join);
		path ++;
		free(join);
	}
	return (NULL);
}


int	main(int ac, char **av, char **envp)
{
	char **path;
	char *ls;
	int	i;

	path = get_path(envp);
	system("leaks pipex");
}