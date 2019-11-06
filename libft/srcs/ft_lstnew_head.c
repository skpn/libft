/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsthead_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 11:28:08 by sikpenou          #+#    #+#             */
/*   Updated: 2019/11/05 23:41:32 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_head	*ft_lstnew_head(t_lst *first, t_lst *last)
{
	t_head	*head;

	if (!(head = (t_head *)easymalloc(sizeof(*head))))
		return (0);
	head->first = first;
	head->last = last;
	head->size = 0;
	return (head);
}
