/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 21:01:06 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/23 21:38:45 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "pipex.h"

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
