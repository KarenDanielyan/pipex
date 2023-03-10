/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:09:15 by kdaniely          #+#    #+#             */
/*   Updated: 2023/02/07 14:04:59 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_putstr(char *str, char bonus, const char *s)
{
	int	count;
	int	i;

	count = 0;
	if (bonus == ' ' && s && ft_strchr(DECIMAL, *(s - 1)))
	{
		i = *(ft_strchr(DECIMAL, *(s - 1))) - '0';
		count = i;
		while (i--)
			write(STDOUT_FILENO, " ", 1);
	}
	if (str)
	{
		while (*str)
		{
			write(STDOUT_FILENO, str++, 1);
			count ++;
		}
	}
	else
	{
		count = 6;
		write(STDOUT_FILENO, "(null)", 6);
	}
	return (count);
}
