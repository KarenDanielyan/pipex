/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:09:15 by kdaniely          #+#    #+#             */
/*   Updated: 2023/02/07 14:03:59 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str)
{
	int	count;

	count = 0;
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
