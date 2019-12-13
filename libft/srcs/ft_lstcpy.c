/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 12:22:43 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/12 18:41:07 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_head	*ft_lstcpy(t_head *original_head)
{
	t_head	*new_head;
	t_lst	*elem;

	if (head && !(new_head = ft_lstnew_head(NULL, NULL)))
		return (0);
	elem = original_head->first;
	while (elem)
	{
		if (!(ft_lstadd_new(new_head, elem->content)))
			return (0);
		elem = elem->next;
	}
	return (new_head);
}
