/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:12:18 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/25 01:59:58 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>

/*	here_doc in case it's bonus project */
# ifdef BONUS
#  define HDOC_FILE	"./hdoc_tmp"

void		hdoc_checker(int ac, char **av);
void		hdoc_handler(char *limiter);
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
# ifndef BONUS

void		redirect_io(int ac, char **av);
# else

void		redirect_io(int ac, char **av, char **path);
# endif

void		loop(int ac, char **av, char **envp, char **path);

/* Command execution and Piping */
void		execute_command(char **cmd, char *path, char **envp);
void		proc_zero(t_process *proc);

t_pipe		get_pipe(void);
t_process	get_process(char **path, char *av);

#endif