/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_graph.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 21:05:19 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/04 15:51:27 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

t_lvl	*init_start_lvl(t_room *start)
{
	t_lvl	 *lvl;

	if (!(lvl = (t_lvl *)easymalloc(sizeof(*lvl))))
		return (0);
	if (!(lvl->rooms = ft_lstnew(start)))
		return (0);
	lvl->dist = 0;
	return (lvl);
}

int		check_graph(t_lem *lem)
{
	if (lem->max_paths < 1 || lem->max_paths > lem->nb_rooms)
		return (0);
	if (lem->shortest != lem->end->dist)
		return (0);
	return (1);
}

void	update_lem_info(t_lem *lem, t_lvl *lvl)
{
	unsigned	size;

	if (ft_lstfind(lvl->rooms, lem->end))
	{
		lem->shortest = lvl->dist;
		lem->end->dist = lvl->dist;
		lem->max_dist = lem->shortest + lem->nb_ants - 1;
	}
	size = lvl->rooms->size;
	if (size < lem->max_paths && lvl->dist > 0 && (lvl->dist < lem->end->dist
		|| lvl->dist == 1))
		lem->max_paths = size;
}

void	add_children_to_next_lvl(t_head *rooms, t_head *children)
{
	t_lst	*elem;
	t_room	*child;

	elem = children->first;
	while (elem)
	{
		child = elem->content;
		if (!child->has_lvl)
		{
			child->has_lvl = 1;
			ft_lstadd_new(rooms, child);
		}
		elem = elem->next;
	}
}

void	get_next_lvl_rooms(t_lem *lem, t_lvl *lvl)
{
	t_lst	*current_rooms;
	t_room	*parent;

	current_rooms = lvl->rooms->first;
	lvl->rooms->first = NULL;
	lvl->rooms->last = NULL;
	while (current_rooms)
	{
		parent = current_rooms->content;
		printf("joining children of:\n");
		print_room(parent);
		printf("to list:\n");
		ft_lstprint(lvl->rooms, "next lvl rooms", NONE);
		if (parent->children->first != NULL)
			add_children_to_next_lvl(lvl->rooms, parent->children);
		else if (parent != lem->end)
			kill_dead_rooms(lem, parent);
		current_rooms = current_rooms->next;
	}
}

int		set_graph(t_lem *lem)
{
	t_lvl	*lvl;

	if (!(lvl = init_start_lvl(lem->start)))
		return (0);
	g_ptr = lem;
	lem->start->dist = 0;
	printf("START OF SET GRAPH\n");
	print_lvl(lvl);
	while (lvl->dist < lem->max_dist && lvl->rooms->first)
	{
		printf("----SETTING LVL %u----\n\n", lvl->dist);
		set_next_lvl_dists(lvl);
		printf("AFTER SETTING DISTS\n");
		print_lvl(lvl);
		set_next_lvl_families(lvl, lem->end);
		printf("AFTER SETTING FAMILIES\n");
		print_lvl(lvl);
		update_lem_info(lem, lvl);
		printf("AFTER UPDATING LEM:\ncurrent dist: %u\nend->dist: %u\n"
				"lvl->rooms: %p\nmax_dist: %u\nmax_paths: %u\n\n"
			, lvl->dist, lem->end->dist, lvl->rooms, lem->max_dist, lem->max_paths);
		//print_rooms(lem->rooms);
		get_next_lvl_rooms(lem, lvl);
		lvl->dist++;
		printf("AFTER GETTING NEXT LVL\n");
		print_lvl(lvl);
	}
	PRINTPOSN;
	if (!(check_graph(lem)))
		return (0);
	PRINTPOSN;
	ft_lstfree_head(&lvl->rooms);
	lvl->rooms = NULL;
	ft_free((void **)&lvl);
	print_rooms(lem->rooms);
	return (1);
}
