/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:42:25 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/08 14:42:37 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_sort(t_lst **begin_list, int (*cmp)())
{
	void		*tmp;
	t_lst		*elem;

	if (!begin_list || !*begin_list || !cmp)
		return ;
	elem = *begin_list;
	while (elem->next)
	{
		if ((*cmp)(elem->content, (elem->next)->content) > 0)
		{
			tmp = elem->content;
			elem->content = (elem->next)->content;
			(elem->next)->content = tmp;
			elem = *begin_list;
		}
		else
			elem = elem->next;
	}
}
