/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:12:18 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/24 21:24:48 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# ifdef LINUX
#  define <sys/wait.h>
# endif

/*
*	pipe(fd) writes in fd[2] input and output file
*	descriptors. To not address in and out as fd[0]
*	and fd[1] we will save them into this structure.
*	This makes code look more human readable.
*/
typedef struct s_pipe
{
	int	in;
	int	out;
}	t_pipe;

/*
*	Process structure to contain path to executable
*	and command arguments. Point is to make code more
*	human readable.
*/
typedef struct s_process
{
	char	*path;
	char	**cmd;
}	t_process;

/* Main logic */
void		redirect_io(int ac, char **av);
void		loop(int ac, char **av, char **envp, char **path);

/* Command execution and Piping */
void		proc_zero(t_process *proc);
void		pipe_close(t_pipe *pip_arr, int len);

t_pipe		*pipe_init(int len);
t_pipe		get_pipe(void);
t_process	*get_process(char **path, char *av);

#endif