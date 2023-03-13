/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:15:49 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/13 16:43:28 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (s)
	{
		while (*(s + len))
			len++;
	}
	return (len);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!dup || !s)
		return (NULL);
	while (*(s + i))
	{
		*(dup + i) = *(s + i);
		i ++;
	}
	*(dup + i) = '\0';
	return (dup);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		range;
	size_t		i;

	if (!s || !(*s))
		return (NULL);
	i = ft_strlen(s);
	range = 0;
	if (start < i)
		range = i - start;
	if (range > len)
		range = len;
	str = (char *)malloc((range + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < range)
	{
		*(str + i) = *(s + start + i);
		i++;
	}
	*(str + i) = '\0';
	return (str);
}

char	*ft_strchr(const char *str, int c)
{
	char	*buf;

	if (!str)
		return (NULL);
	buf = (char *)str;
	while (*buf)
	{
		if (*buf == (unsigned char)(c & 0xFF))
			return (buf);
		buf++;
	}
	if (*buf == c)
		return (buf);
	else
		return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	long	i;
	char	*join;

	if (!s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	join = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!join)
		return (NULL);
	i = -1;
	while ((size_t)(++i) < len1)
		*(join + i) = *(s1 + i);
	--i;
	while ((size_t)(++i) < len1 + len2)
		*(join + i) = *(s2 + i - len1);
	*(join + len1 + len2) = '\0';
	if (s1)
		free(s1);
	return (join);
}
