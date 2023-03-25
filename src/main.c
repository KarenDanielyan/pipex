/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:11:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/25 17:30:53 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "pipex.h"


static t_args	args_init(int ac, char **av, char **envp)
{
	t_args	args;

	args.ac = ac;
	args.av = av + 2;
	args.envp = envp;
	args.path = get_path(envp);
	args.pip = redirect_io(ac, av);
	return (args);
}

int	main(int ac, char **av, char **envp)
{
	t_args		args;

	parse(ac);
	args = args_init(ac , av, envp);
	loop(args, (ac - 3));
	free_2d(args.path);
	return (0);
}
