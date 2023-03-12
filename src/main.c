/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:11:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/12 21:39:00 by kdaniely         ###   ########.fr       */
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
		{
			path = *(envp + i);
			break;
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

static	char	*get_exec(char **path, char *cmd)
{
	char	*cmd_w_slash;
	char	*join;

	cmd_w_slash = ft_strjoin("/", cmd);
	while (path) 
	{
		join = ft_strjoin(*path, cmd_w_slash);
		if (access(join, X_OK) == 0)
			break;
		path ++;
		free(join);
		join = NULL;
	}
	free(cmd_w_slash);
	return (join);
}


int	main(int ac, char **av, char **envp)
{
	char **path;
	char *ls;
	int	i;

	path = get_path(envp);
	ls = get_exec(path, "ls");
	ft_printf("%s\n", ls);
	//system("leaks pipex");
}