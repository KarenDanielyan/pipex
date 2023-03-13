/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:55:05 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/13 16:15:01 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <errno.h>
#include "parse.h"
#include "pipex.h"

#define EINARG	"Argument list too short."

static	void	get_args(int ac, char **av, t_list **queue)
{
	int	i;
	t_list	*tmp;

	i = 1;
	while (i < ac)
	{
		tmp = ft_lstnew(ft_split(av[i], ' '));
		if (!tmp)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		ft_lstadd_back(queue, tmp);
		i ++;
	}
}

void	parse(int ac, char **av, t_list **queue)
{
	int		i;

	i = 1;
	if (ac < 5)
	{
		ft_printf("Error: %s\n", EINARG);
		exit(EXIT_FAILURE);
	}
	get_args(ac, av, queue);
}

t_type	get_arg_type(char **av)
{
	int	len;

	len = ft_strlen_2d((const char **)av);
	if (len > 1)
		return (COMMAND);
	else if (len == 1 && ft_strncmp(*av, "here_doc", 8) == 0)
		return (HERE_DOC);
	else
		return (FIL);
}