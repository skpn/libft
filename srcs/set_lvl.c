/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_lvl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 22:11:27 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/07 19:05:07 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

void		set_next_lvl_dists(t_lvl *lvl)
{
	unsigned	new_dist;
	t_lst		*lvl_rooms_lst;
	t_room		*parent;
	t_lst		*sisters_lst;
	t_room		*sister;

	lvl_rooms_lst = lvl->rooms->first;
	new_dist = lvl->dist + 1;
	while (lvl_rooms_lst)
	{
		parent = lvl_rooms_lst->content;
		sisters_lst = parent->sisters->first;
		while (room_sisters)
		{
			sister = room_sisters->content;
			room_sisters = room_sisters->next;
			if (sister->dist > new_dist)
				sister->dist = new_dist;
		}
		lvl_rooms_lst = lvl_rooms_lst->next;
	}
}
