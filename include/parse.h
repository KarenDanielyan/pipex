/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:00:47 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/21 19:01:11 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include <ft_printf.h>
#include <libft.h>
#include <string.h>
#include <errno.h>

/* Main function */
void	parse(int ac, char **av);

/*
*	To differenciate between arguments provided by end-user
*	We propose types enumerable that consists of following:
*		1. FIL	- argument is a file that has r | w permissions,
			but not x permission.
		2. CMD	- argument is an executable file.
		3. HDOC	- here_doc argument to handle deleimited input.
		4. NVA	- If its none of the above then its a non valid
			argument.
*/
typedef enum e_type
{
	FIL,
	CMD,
	HDOC,
	NVA
}	t_type;

/*
*	Description: get_type() return type of the provided
*	argument. If it's unknown type it will return NVA == 3.
*/
t_type	get_type(char *av, char **path);

/*
*	Decription:	get_file_path() finds specified command/file,
*	by combining it with paths specified in PATH variable,
*	to see if file like this exists and is an executable.
*
*	Return Value: path to the executable, or NULL if there is none.
*/
char	*get_file_path(char **path, char *file);

/*
*	Description: get_path() extracts PATH variable from env.
*
*	Return Value: The PATH variable.
*
*	NOTE: If there is no PATH in env, the process will terminate.
*/
char	**get_path(char **envp);

/*
*	Description: get_type() returns the argument type of
*	the argument, it 
*/

/* Helper Functions */
/*
*	Description: free_2d() frees a 2-dimensional array
*	pointed by ptr.
*/
void	free_2d(char **ptr);

#endif