/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:25:53 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/14 21:57:35 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <limits.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 0xFFFF
# endif

size_t	gnl_strlen(const char *s);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
char	*gnl_strchr(const char *str, int c);
char	*gnl_strdup(const char *s);
char	*gnl_strjoin(char *s1, char *s2);

/*
*	Reference: DNE
*
*	Description: Returns a line read from file pointed by
*	file descriptor. If fd is invalid, function returns
*	NULL;
*	NOTE: In order to not have leaks, run get_next_line() function
*	with -42 parameter in order to free the static allocated space
*	before ending program execution.
*
*	Return Value: C-standard string with nl, or NULL on invalid fd.
*/
char	*get_next_line(int fd);

#endif
