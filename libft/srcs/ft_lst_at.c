/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:26:10 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/08 14:26:14 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst		*ft_lst_at(t_lst *begin_list, unsigned int nbr)
{
	unsigned int	pos;
	t_lst			*elem;

	pos = 1;
	if (!begin_list || nbr < 1)
		return (NULL);
	elem = begin_list;
	while (elem && pos < nbr)
	{
		elem = elem->next;
		pos++;
	}
	if (pos == nbr)
		return (elem);
	else
		return (NULL);
}
