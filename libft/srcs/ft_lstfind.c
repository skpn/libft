/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:07:51 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/30 17:29:51 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
t_lst		*ft_lstfind(t_lst *begin_list, void *match)
{
	t_lst		*elem;

	if (!begin_list || !match)
		return (NULL);
	elem = begin_list;
	while (elem)
	{
		if (elem->content == match)
			return (elem);
		elem = elem->next;
	}
	return (NULL);
}
