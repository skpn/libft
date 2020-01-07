/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_lvl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 22:11:27 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/07 22:40:59 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

void		sort_lvl_sisters(t_lvl *lvl)
{
	t_lst		*transfer;
	t_lst		*rooms_lst;
	t_lst		*sisters_lst;
	t_room		*room;
	t_room		*sister;

	rooms_lst = lvl->rooms->first;
	while (rooms_lst)
	{
		room = rooms_lst->content;
		rooms_lst = rooms_lst->next;
		sisters_lst = room->sisters->first;
		while (sisters_lst)
		{
			sister = sisters_lst->content;
			sisters_lst = sisters_lst->next;
			if (sister->dist < room->dist)
			{
				transfer = ft_lstpop(room->sisters, sister);
				if (transfer)
					ft_lstadd(room->sisters, transfer);
			}
		}
	}
}

void		set_next_lvl_dists(t_lvl *lvl)
{
	unsigned	new_dist;
	t_lst		*rooms_lst;
	t_lst		*sisters_lst;
	t_room		*room;
	t_room		*sister;

	rooms_lst = lvl->rooms->first;
	new_dist = lvl->dist + 1;
	while (rooms_lst)
	{
		room = rooms_lst->content;
		rooms_lst = rooms_lst->next;
		sisters_lst = room->sisters->first;
		while (sisters_lst)
		{
			sister = sisters_lst->content;
			sisters_lst = sisters_lst->next;
			if (sister->dist > new_dist)
				sister->dist = new_dist;
		}
	}
	sort_lvl_sisters(lvl);
}
