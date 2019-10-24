/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:56:31 by sikpenou          #+#    #+#             */
/*   Updated: 2019/09/30 20:36:18 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_lstprint(t_lst *elem, int opt)
{
	int		i;

	i = 0;
	if (!elem)
		return (ft_putstr_ret("--\nempty list\n--\n"));
	opt > 1 ? ft_putstr("\n--\nlist start\n--\n") : 0;
	while (elem)
	{
		if (opt > 1)
		{
			ft_putstr("pos ");
			ft_putnbr(i++);
			ft_putstr(": '");
		}
		ft_putstr(elem->content);
		elem = elem->next;
		ft_putstr(opt > 1 ? "'\n" : "\n");
	}
	if (opt > 1)
		ft_putstr("--\nlist end\n--\n\n");
	else
		ft_putstr("\n");
	return (0);
}
