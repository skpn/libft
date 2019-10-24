/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_merge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:42:56 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/08 14:42:58 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_merge(t_lst **begin_list1, t_lst *begin_list2)
{
	t_lst		*elem;

	if (!begin_list1)
		return ;
	if (!*begin_list1)
	{
		if (!begin_list2)
			return ;
		else
		{
			*begin_list1 = begin_list2;
			return ;
		}
	}
	elem = *begin_list1;
	while (elem->next)
		elem = elem->next;
	elem->next = begin_list2;
	return ;
}
