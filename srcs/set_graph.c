/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_graph.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 21:05:19 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/06 14:59:03 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static int	add_children_to_next_lvl(t_head *rooms, t_head *children)
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
			if (!(ft_lstadd_new(rooms, child)))
				return (0);
		}
		elem = elem->next;
	}
	return (1);
}

static int	get_next_lvl_rooms(t_lem *lem, t_lvl *lvl)
{
	t_lst	*current_rooms;
	t_lst	*tmp;
	t_room	*parent;

	current_rooms = lvl->rooms->first;
	lvl->rooms->first = NULL;
	lvl->rooms->last = NULL;
	while (current_rooms)
	{
		parent = current_rooms->content;
		if (parent->children->first != NULL)
		{
			if (!add_children_to_next_lvl(lvl->rooms, parent->children))
				return (0);
		}
		else if (parent != lem->end)
			kill_dead_rooms(lem, parent);
		tmp = current_rooms;
		current_rooms = current_rooms->next;
		ft_lstfree_elem(&tmp, FREE_LINKS);
	}
	return (1);
}

static int	set_lvls(t_lem *lem, t_lvl *lvl)
{
	t_lst	*end_elem;

	while (lvl->dist < lem->max_dist && lvl->rooms->first)
	{
		set_next_lvl_dists(lvl);
		set_next_lvl_families(lvl, lem->end);
		if (lvl->rooms->size < lem->max_paths && lvl->dist > 0
			&& (lvl->dist < lem->end->dist || lvl->dist == 1))
			lem->max_paths = lvl->rooms->size;
		if (!get_next_lvl_rooms(lem, lvl))
		{
			free_lvl(&lvl);
			return (0);
		}
		if (lvl->dist + 1 == lem->end->dist)
		{
			if ((end_elem = ft_lstpop(lvl->rooms, lem->end)))
				ft_lstfree_elem(&end_elem, FREE_LINKS);
			lem->shortest = lvl->dist + 2;
			lem->max_dist = lem->shortest + lem->nb_ants - 1;
		}
		lvl->dist++;
	}
	return (1);
}

static int	set_first_lvl(t_lem *lem, t_lvl *lvl)
{
	if (!(ft_lstadd_new(lvl->rooms, lem->start)))
	{
		free_lvl(&lvl);
		return (0);
	}
	lem->start->dist = 0;
	return (1);
}

int			set_graph(t_lem *lem)
{
	t_lvl	*lvl;

	if (!(lvl = alloc_new_lvl())
		|| !set_first_lvl(lem, lvl) || !set_lvls(lem, lvl))
		return (0);
	if (lem->start)
		lem->start->dist = 0;
	else
	{
		free_lvl(&lvl);
		return (0);
	}
	if ((lem->max_paths < 1 || lem->max_paths > lem->table->elems
		|| lem->shortest != lem->end->dist + 1)
			&& !ft_lstfind(lem->start->children, lem->end))
	{
		free_lvl(&lvl);
		return (PARSING_ERROR);
	}
	kill_end_children(lem->end, lem->max_dist);
	free_lvl(&lvl);
	return (1);
}
