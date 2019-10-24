/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:05:28 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/08 18:05:29 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_lst	*ft_lstmap(t_lst *lst, t_lst *(*f)(t_lst *elem))
{
	t_lst	*elem;

	if (lst)
	{
		if (!(elem = (t_lst *)easymalloc(sizeof(t_lst))))
			return (NULL);
		elem = f(lst);
		lst = lst->next;
		elem->next = ft_lstmap(lst, f);
		return (elem);
	}
	return (NULL);
}
