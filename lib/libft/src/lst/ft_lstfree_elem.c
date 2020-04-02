/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree_elem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 12:00:23 by sikpenou          #+#    #+#             */
/*   Updated: 2020/03/27 11:21:20 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstfree_elem(t_lst **elem, int opt)
{
	if (opt == FREE_BOTH || opt == FREE_CONTENT)
		easyfree((void **)&(*elem)->content);
	if (opt == FREE_BOTH || opt == FREE_STRUCT)
		easyfree((void **)elem);
}
