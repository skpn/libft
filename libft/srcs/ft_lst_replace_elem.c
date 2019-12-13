/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:06:05 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/13 11:42:41 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpop(t_head *head, t_lst *original, t_lst *replacement)
{
	t_lst	*elem;

	if (original == head->first)
		head->first = elem->next;
	else
		elem->prev->next = elem->next;
	if (head->last == elem)
		head->last = elem->prev;
	else
		elem->next->prev = elem->prev;
}
