/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:45:39 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/19 13:51:34 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

void	kill_end_children(t_room *end, unsigned max_dist)
{
	t_lst	*child_elem;
	t_lst	*transfer;
	t_room	*child;

	child_elem = end->children->first;
	while (child_elem)
	{
		child = child_elem->content;
		child_elem = child_elem->next;
//		printf("END CHILD:\n");
//		print_room(child);
		transfer = ft_lstpop(end->children, child);
		if (child->dist <= max_dist)
			ft_lstadd(end->parents, transfer);
	}
}

void	kill_dead_rooms(t_lem *lem, t_room *dead_room)
{
	t_lst	*parents_lst;
	t_room	*parent;

	if (dead_room->children->first != NULL || dead_room->parents->size > 1)
		return ;
//	printf("killing room:\n");
//	print_room(dead_room);
	parents_lst = dead_room->parents->first;
	while (parents_lst)
	{
		parent = (t_room *)parents_lst->content;
		parents_lst = parents_lst->next;
		ft_lstpop(dead_room->parents, parent);
		ft_lstpop(parent->children, dead_room);
		if (parent->children->first == NULL)
			kill_dead_rooms(lem, parent);
	}
	free_room(lem->rooms, &dead_room);
}
