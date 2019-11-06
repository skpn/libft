/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:05:42 by sikpenou          #+#    #+#             */
/*   Updated: 2019/11/03 12:08:42 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstnew_elem(void *content)
{
	t_lst	*new_elem;

	if (!(new_elem = (t_lst *)easymalloc(sizeof(t_lst))))
		return (NULL);
	ft_memset(new_elem, 0, sizeof(*new_elem));
	new_elem->content = content;
	return (new_elem);
}
