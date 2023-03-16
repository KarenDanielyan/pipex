/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:00:47 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/16 18:27:42 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

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

/* Helper Functions */
/*
*	Description: free_2d() frees a 2-dimensional array
*	pointed by ptr.
*/
void	free_2d(char **ptr);

#endif