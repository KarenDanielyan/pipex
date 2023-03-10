/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:50:08 by kdaniely          #+#    #+#             */
/*   Updated: 2023/02/07 14:04:54 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_putunbr(unsigned int nbr)
{
	char	*num;
	int		count;

	num = ft_itoa_base(nbr, DECIMAL);
	count = ft_putstr(num, 0, NULL);
	free(num);
	return (count);
}

int	ft_putnbr(int nbr, char bonus)
{
	char	*num;
	int		count;

	count = 0;
	if (nbr >= 0)
	{
		if (bonus == ' ')
		{
			write(STDOUT_FILENO, " ", 1);
			count++;
		}
		else if (bonus == '+')
		{
			write(STDOUT_FILENO, "+", 1);
			count++;
		}
	}
	num = ft_itoa_base(nbr, DECIMAL);
	count += ft_putstr(num, 0, NULL);
	free(num);
	return (count);
}

int	ft_putptr(uintptr_t ptr, char *base)
{
	uintptr_t	temp;
	uintptr_t	base_len;	
	int			count;

	temp = ptr;
	count = 0;
	base_len = ft_strlen(base);
	if (temp > (base_len - 1))
	{
		count += ft_putptr(temp / base_len, base);
		count += ft_putptr(temp % base_len, base);
	}
	else
	{
		write(STDOUT_FILENO, (base + temp), 1);
		count ++;
	}
	return (count);
}

int	ft_puthex(unsigned int nbr, const char *f_str, char bonus)
{
	char	*num;
	int		count;

	count = 0;
	if (bonus == '#' && nbr)
	{
		if (*f_str == 'x')
			write(STDOUT_FILENO, "0x", 2);
		else if (*f_str == 'X')
			write(STDOUT_FILENO, "0X", 2);
		count += 2;
	}
	if (*f_str == 'x')
		num = ft_itoa_base(nbr, L_HEX);
	else
		num = ft_itoa_base(nbr, B_HEX);
	count += ft_putstr(num, 0, NULL);
	free(num);
	return (count);
}
