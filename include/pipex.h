/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:12:18 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/16 16:23:30 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BONUS
#  define BONUS 0
# endif

typedef struct s_pipe
{
	int	in;
	int	out;
}	t_pipe;

typedef struct s_process
{
	char	*path;
	char	**cmd;
}	t_process;

t_pipe		get_pipe(void);
t_process	get_process(char **path, char *av);
void	proc_zero(t_process *proc);

#endif