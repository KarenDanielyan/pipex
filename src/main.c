/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:11:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/16 18:46:29 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	char	**path;

	if (ac < 5)
		return (1);
	path = get_path(envp);
	redirect_io(ac, av);
	loop(ac, av, envp, path);
	free_2d(path);
	system("leaks pipex");
	return (0);
}
