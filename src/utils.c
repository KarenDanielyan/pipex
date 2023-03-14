/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:44:29 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/14 21:53:49 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <ft_printf.h>
#include "parse.h"

char	*get_file_path(char **path, char *file)
{
	char	*file_w_slash;
	char	*join;

	if (access(file, X_OK) == 0)
		return (file);
	file_w_slash = ft_strjoin("/", file);
	while (path)
	{
		join = ft_strjoin(*path, file_w_slash);
		if (access(join, X_OK) == 0 || !join)
			break;
		path ++;
		free(join);
		join = NULL;
	}
	free(file_w_slash);
	return (join);
}

char	**get_path(char **envp)
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

void	fork_in_main(t_list **pid_l)
{
	t_list	*head;
	int	*n;

	head = *pid_l;
	if (head)
	{
		if (ft_lstsize(head) >= 1 && *((int *)(head->content)) != 0)
		{
			n = malloc(sizeof(int));
			*n = fork();
			ft_lstadd_back(pid_l, ft_lstnew(n));
		}
	}
	else
	{
		n = malloc(sizeof(int));
		*n = fork();
		ft_lstadd_back(pid_l, ft_lstnew(n));
	}
}

char	*read_file(int	fd)
{
	char	*content;
	char	*tmp;
	
	tmp = get_next_line(fd);
	content = NULL;
	while (tmp)
	{
		if (content)
		{
			content = ft_strjoin(content, tmp);
			free(tmp);
		}
		else
			content = tmp;
		tmp = get_next_line(fd);
	}
	return (content);
}