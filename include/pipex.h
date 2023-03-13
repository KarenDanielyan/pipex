/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:12:18 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/13 20:20:35 by kdaniely         ###   ########.fr       */
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
	char	**command;
}	t_process;


typedef enum	e_type
{
	FIL,
	COMMAND,
	HERE_DOC
}	t_type;

t_pipe	get_pipe(void);
t_type	get_arg_type(char **av);

#endif