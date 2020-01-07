/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:45:39 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/07 19:05:06 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

void	kill_end_dangling_rooms(t_room *end, unsigned max_dist)
{
	t_lst	*popped_room_lst;
	t_lst	*sister_lst;
	t_room	*sister;

	sisters_lst = end->sisters_lst->first;
	while (sisters_lst)
	{
		sister = sisters_lst->content;
		sisters_lst = sisters_lst->next;
		if (sister->sisters->disttransfer = ft_lstpop(end->sisterren, sister);
		if (sister->dist <= max_dist)
			ft_lstadd(end->parents, transfer);
		else
			ft_lstfree_elem(&transfer, FREE_LINKS);
	}
}

/*
void	kill_dead_rooms(t_lem *lem, t_room *dead_room)
{
	t_lst		*parents_lst;
	t_lst		*popped;
	t_room		*parent;
	t_h_elem	*dead_room_hash_elem;

//	if (dead_room == lem->start)
//		lem->start = NULL;
	if (dead_room->sisters->size > 1)
		return ;
	parents_lst = dead_room->parents->first;
	while (parents_lst)
	{
		parent = (t_room *)parents_lst->content;
		parents_lst = parents_lst->next;
		if ((popped = ft_lstpop(dead_room->parents, parent)))
			ft_lstfree_elem(&popped, FREE_LINKS);
		if ((popped = ft_lstpop(parent->children, dead_room)))
			ft_lstfree_elem(&popped, FREE_LINKS);
		if (parent->children->first == NULL)
			kill_dead_rooms(lem, parent);
	}
	if (!(dead_room_hash_elem = ft_hash_pop_elem(lem->table, dead_room->name)))
		return ;
	ft_hash_free_elem(lem->table, dead_room_hash_elem, FREE_BOTH);
}
*/
