/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:11:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/25 02:47:21 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	char		**path;
	int			offset;

	path = get_path(envp);
	if (parse(ac, av, path) == 1)
		offset = 3;
	else
		offset = 2;
	loop((ac - (offset + 1)), (av + offset), envp, path);
	if (offset == 3)
		unlink(HDOC_FILE);
	free_2d(path);
	pause();
	return (0);
}
