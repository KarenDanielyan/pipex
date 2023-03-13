/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:00:47 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/13 16:31:35 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <libft.h>

void	parse(int ac, char **av, t_list **queue);

/* Utility functions */
/*
*	Decription:	get_exec() finds specified command,
*	by combining it with paths specified in PATH variable,
*	to see if file like this exists and is an executable.
*
*	Return Value: path to the executable, or NULL if there is none.
*/
char	*get_exec(char **path, char *cmd);
/*
*	Description: get_path() extracts PATH variable from env.
*
*	Return Value: The PATH variable.
*
*	NOTE: If there is no PATH in env, the process will terminate.
*/
char	**get_path(char **envp);
/*
*	Description: Creates a process that is child to main process.
*
*	Return Value: None
*/
void	fork_in_main(t_list **pid_l);

char	*read_file(int fd);

char	*get_next_line(int fd);
#endif