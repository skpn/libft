/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:42:17 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/08 14:42:18 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst		*ft_lst_find(t_lst *begin_list, void *content_ref
			, int (*cmp)(void *, void *), int *c)
{
	t_lst		*elem;

	if (!begin_list || !content_ref || !cmp || !c)
		return (NULL);
	elem = begin_list;
	*c = 0;
	while (elem)
	{
		*c = *c + 1;
		if ((*cmp)(elem->content, content_ref) == 0)
			return (elem);
		elem = elem->next;
	}
	*c = -1;
	return (NULL);
}
