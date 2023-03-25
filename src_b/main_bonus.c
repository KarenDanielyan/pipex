/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:11:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/25 16:53:28 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "pipex.h"


static t_args	args_init(int ac, char **av, char **envp, int offset)
{
	t_args	args;

	args.ac = ac;
	args.av = av + offset;
	args.envp = envp;
	args.path = get_path(envp);
	args.pip = redirect_io(ac, av, args.path);
	return (args);
}

int	main(int ac, char **av, char **envp)
{
	t_args		args;
	int			offset;
	char		**path;


	path = get_path(envp);
	if (parse(ac, av, path) == 1)
		offset = 3;
	else
		offset = 2;
	free_2d(path);
	args = args_init(ac , av, envp, offset);
	loop(args, (ac - (offset + 1)));
	if (offset == 3)
		unlink(HDOC_FILE);
	free_2d(args.path);
	return (0);
}
