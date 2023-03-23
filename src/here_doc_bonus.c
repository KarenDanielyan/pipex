/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:23:36 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/23 19:42:44 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "pipex.h"
# include "parse.h"
# include "get_next_line_bonus.h"
# include <fcntl.h>

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

void	hdoc_handler(char *limiter)
{
	int		fd;
	char	*str;
	int		limit_len;

	fd = open(HDOC_FILE, O_RDWR | O_APPEND | O_CREAT, 0600);
	limit_len = ft_strlen(limiter);
	if (limit_len == 0 || fd == -1)
	{
		if (limit_len == 0)
			ft_putstr_fd(INVAL_LIMIT, STDERR_FILENO);
		if (fd == -1)
			ft_putstr_fd(INTERNAL_MSG, STDERR_FILENO);
		unlink(HDOC_FILE);
		exit(EXIT_FAILURE);
	}
	str = get_next_line(STDIN_FILENO);
	while (str != NULL && ft_strncmp(str, limiter, (ft_strlen(str) - 1)) != 0)
	{
		write(fd, str, ft_strlen(str));
		free(str);
		str = get_next_line(STDIN_FILENO);
	}
	if (str)
		free(str);
	close(fd);
}
#endif