/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:47:39 by kdaniely          #+#    #+#             */
/*   Updated: 2023/02/07 13:48:33 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdint.h>

# define OFFSET			'0'
# define BONUS			"# +"
# define FORMAT_FLAGS 	"cspdiuxX%"
# define ESCAPE_SEQ		"\\\"\t\b\a\?\r\f\v\n"
# define DECIMAL		"0123456789"
# define OCTAL			"01234567"
# define B_HEX			"0123456789ABCDEF"
# define L_HEX			"0123456789abcdef"

/* Helper Functions */
char	*ft_itoa_base(long n, const char *base);
char	*ft_strchr(const char *str, int c);

int		ft_putchar(char c);
int		ft_putunbr(unsigned int nbr);
int		ft_putnbr(int nbr, char bonus);
int		ft_putptr(uintptr_t ptr, char *base);
int		ft_putstr(char *str, char bonus, const char *s);
int		ft_puthex(unsigned int nbr, const char *f_str, char bonus);

size_t	ft_strlen(const char *str);

/* Printf */
int		ft_printf(const char *s, ...);

#endif
