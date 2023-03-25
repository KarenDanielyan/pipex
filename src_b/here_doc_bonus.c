/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:23:36 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/25 20:38:30 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "get_next_line_bonus.h"
#include "pipex.h"
#include "parse.h"

#define INVAL_LIMIT		"Error: Invalid Limiter for here_doc.\n"
#define INTERNAL_MSG	"Internal Error: Unable to perform here_doc.\n"

void	hdoc_checker(int ac, char **av)
{
	(void)av;
	if (ac < 6)
	{
		ft_putstr_fd("Pipex: Insufficient number of agruments.", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

static void	arg_check(int limit_len, int fd)
{
	if (limit_len == 0 || fd == -1)
	{
		if (limit_len == 0)
			ft_putstr_fd(INVAL_LIMIT, STDERR_FILENO);
		if (fd == -1)
			ft_putstr_fd(INTERNAL_MSG, STDERR_FILENO);
		if (fd != -1)
		{
			close(fd);
			unlink(HDOC_FILE);
		}
		exit(EXIT_FAILURE);
	}
}

static	int	len_handler(int str_len, int limit_len)
{
	if ((str_len - 1) > limit_len)
		return (str_len - 1);
	else
		return (limit_len);
}

void	hdoc_handler(char *limiter)
{
	int		fd;
	char	*str;
	int		limit_len;

	fd = open(HDOC_FILE, O_RDWR | O_APPEND | O_CREAT, 0600);
	limit_len = ft_strlen(limiter);
	arg_check(limit_len, fd);
	while (1)
	{
		str = get_next_line(STDIN_FILENO);
		if (!str || ft_strncmp(str, limiter, len_handler(ft_strlen(str), limit_len)) == 0)
			break ;
		write(fd, str, ft_strlen(str));
		free(str);
	}
	if (str)
		free(str);
	close(fd);
}
