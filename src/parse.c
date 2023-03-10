/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:55:05 by kdaniely          #+#    #+#             */
/*   Updated: 2023/03/09 20:15:07 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>
#include <errno.h>

void	parse(int ac, char **av, t_list **queue)
{
	int		i;
	t_list	*tmp;

	i = 1;
	if (ac < 5)
	{
		ft_printf("Error: %s\n", strerror(EINVAL));
		exit(EINVAL);
	}
	while (i < ac)
	{
		tmp = ft_lstnew(ft_strdup(av[i]));
		if (!tmp)
		{
			ft_printf("Error: %s\n", strerror(ENOMEM));
			exit(ENOMEM);
		}
		ft_lstadd_back(queue, tmp);
		i++;
	}
}