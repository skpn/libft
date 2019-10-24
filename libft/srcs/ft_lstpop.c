/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:06:05 by sikpenou          #+#    #+#             */
/*   Updated: 2019/09/30 21:32:59 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstpop(t_lst **begin, void *match)
{
	t_lst		*elem;
	t_lst		*tmp;

	if (*begin == match || (*begin)->content == match)
	{
		tmp = *begin;
		(*begin)->next ? ((*begin)->next->last = (*begin)->last) : 0;
		*begin = (*begin)->next;
		return (tmp);
	}
	elem = (*begin)->last == match || (*begin)->last->content == match
		? (*begin)->last : *begin;
	while (elem->next)
	{
		if (elem->next == match || elem->next->content == match)
		{
			tmp = elem->next;
			elem->next = elem->next->next;
			elem->next ? 0 : ((*begin)->last = elem);
			return (tmp);
		}
		elem = elem->next;
	}
	return (NULL);
}
