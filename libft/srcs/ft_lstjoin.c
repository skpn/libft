/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:31:04 by sikpenou          #+#    #+#             */
/*   Updated: 2019/11/03 21:07:59 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstjoin(t_head *dst, t_head *src)
{
	if (src->first)
		src->first->prev = dst->last;
	if (dst->last)
		dst->last->next = src->first;
	dst->last = src->last;
}
