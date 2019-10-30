/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:07:51 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/30 16:17:23 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst		*ft_lstfind(t_lst *begin_list, void *match)
{
	t_lst		*elem;

	if (!begin_list || !match)
		return (NULL);
	elem = begin_list;
	while (elem)
	{
		if (elem == match || !ft_strcmp(elem->content, match))
			return (elem);
		elem = elem->next;
	}
	return (NULL);
}
