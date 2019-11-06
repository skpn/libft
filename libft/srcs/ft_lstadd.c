/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:03:41 by sikpenou          #+#    #+#             */
/*   Updated: 2019/11/03 13:15:07 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_head *head, t_lst *new)
{
	head->size++;
	new->next = head->first;
	head->first = new;
	if (new->next)
	{
		new->next->prev = new;
	}
	else
	{
		head->last = new;
	}
}
