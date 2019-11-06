/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 13:03:23 by sikpenou          #+#    #+#             */
/*   Updated: 2019/11/03 13:06:19 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	swap_first(t_head *head_1, t_head *head_2)
{
	t_lst	*tmp_first;

	tmp_first = head_1->first;
	head_1->first = head_2->first;
	head_2->first = tmp_first;
}

void	swap_last(t_head *head_1, t_head *head_2)
{
	t_lst	*tmp_last;

	tmp_last = head_1->last;
	head_1->last = head_2->last;
	head_2->last = tmp_last;
}

void	ft_lstswap(t_head *head_1, t_head *head_2)
{
	swap_first(head_1, head_2);
	swap_last(head_1, head_2);
}
