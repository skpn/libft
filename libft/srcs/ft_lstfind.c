/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:07:51 by sikpenou          #+#    #+#             */
/*   Updated: 2019/11/03 22:40:56 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstfind(t_head *head, void *match)
{
	t_lst	*elem;

	if (match && head->first)
	{
		if (head->last == match || head->last->content == match)
			elem = head->last;
		else
			elem = head->first;
		while (elem)
		{
			if (elem == match || elem->content == match)
				return (elem);
			elem = elem->next;
		}
	}
	return (NULL);
}
