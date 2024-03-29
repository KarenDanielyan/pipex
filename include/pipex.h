/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:12:18 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/25 17:31:15 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

/* here_doc in case of bonus */
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

/* NOTE: Fuck norminette */
typedef struct s_args
{
	int		ac;
	char	**av;
	char	**envp;
	char	**path;
	t_pipe	pip;
}	t_args;

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

t_pipe		redirect_io(int ac, char **av);
# else

t_pipe		redirect_io(int ac, char **av, char **path);
# endif

void		loop(t_args args, int cmd_count);

/* Command execution and Piping */
void		pipe_close(t_pipe *pip_arr, int len);
void		proc_free(t_process *proc);

t_pipe		*pipe_init(int len);
t_pipe		get_pipe(void);
t_process	*get_process(char **path, char *av);

#endif