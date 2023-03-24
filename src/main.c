/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:11:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/25 02:20:29 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	char		**path;

	path = get_path(envp);
	parse(ac, av);
	loop((ac - 3), (av + 2), envp, path);
	free_2d(path);
	return (0);
}
