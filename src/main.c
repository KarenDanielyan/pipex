/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:11:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/23 19:24:30 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "pipex.h"

#ifndef BONUS
int	main(int ac, char **av, char **envp)
{
	char	**path;

	path = get_path(envp);
	parse(ac, av);
	loop(ac, av, envp, path);
	free_2d(path);
	return (0);
}
#else
int	main(int ac, char **av, char **envp)
{
	char	**path;

	path = get_path(envp);
	parse(ac, av, path);
	loop(ac, av, envp, path);
	free_2d(path);
	unlink(HDOC_FILE);
	return (0);
}
#endif