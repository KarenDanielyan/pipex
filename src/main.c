/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:11:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/13 20:35:11 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <libft.h>
#include <fcntl.h>
#include "parse.h"
#include "pipex.h"

/*static void	check_input(int ac, char **av)
{
	if (ac < 5 && !BONUS)
	{
		ft_printf("Insufficient number of arguments.\n");
		exit(EXIT_FAILURE);
	}
	if (get_arg_type(av[0]) == FIL && get_arg_type(av[ac - 1]) == FIL)
	{
		if (access(av[0], F_OK) == -1 || access(av[ac - 1], F_OK) == -1)
		{
			perror("Access: ");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		ft_printf("First and last arguments are not files!!!\n");
		exit(EXIT_FAILURE);
	}
}*/

static void	redirect_io(int ac, char **av)
{
	int	fd[2];
	
	fd[0] = open(av[1], O_RDONLY);
	fd[1] = open(av[ac - 1], O_WRONLY);
	if (fd[0] == -1 || fd[1] == -1)
	{
		perror("Open: ");
		exit(EXIT_FAILURE);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
}

int	main(int ac, char **av, char **envp)
{
	char **cmd = ft_split("wc -l", ' ');
	redirect_io(ac, av);
	execve("/usr/bin/wc", cmd, envp);
	return (0);
}