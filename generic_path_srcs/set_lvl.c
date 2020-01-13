/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_lvl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 22:11:27 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/06 10:45:26 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static void	set_parent_as(int opt, t_room *parent, t_room *child)
{
	t_lst	*transfer;

	if (opt == PARENT || opt == BROTHER)
	{
		transfer = ft_lstpop(child->children, parent);
		ft_lstadd(child->parents, transfer);
	}
	if (opt == CHILD || opt == BROTHER)
	{
		transfer = ft_lstpop(parent->children, child);
		ft_lstadd(parent->parents, transfer);
	}
}

static void	set_children_families(t_room *parent, t_room *end)
{
	t_lst	*room_children;
	t_lst	*tmp;
	t_room	*child;

	room_children = parent->children->first;
	while (room_children)
	{
		tmp = room_children->next;
		child = room_children->content;
		if (child->dist > parent->dist)
		{
			set_parent_as(PARENT, parent, child);
		}
		else if (child->dist == parent->dist && child != end)
		{
			set_parent_as(BROTHER, parent, child);
		}
		else
		{
			if (child != end)
				set_parent_as(CHILD, parent, child);
		}
		room_children = tmp;
	}
}

void		set_next_lvl_families(t_lvl *lvl, t_room *end)
{
	t_lst		*lvl_parents;
	t_room		*parent;

	lvl_parents = lvl->rooms->first;
	while (lvl_parents)
	{
		parent = lvl_parents->content;
		if (parent != end)
			set_children_families(parent, end);
		lvl_parents = lvl_parents->next;
	}
}

static void	set_children_dists(t_room *parent, unsigned new_dist)
{
	t_lst	*room_children;
	t_room	*child;

	room_children = parent->children->first;
	while (room_children)
	{
		child = room_children->content;
		if (child->dist > new_dist)
			child->dist = new_dist;
		room_children = room_children->next;
	}
}

void		set_next_lvl_dists(t_lvl *lvl)
{
	t_lst		*lvl_parents;
	t_room		*parent;
	unsigned	new_dist;

	lvl_parents = lvl->rooms->first;
	new_dist = lvl->dist + 1;
	while (lvl_parents)
	{
		parent = lvl_parents->content;
		set_children_dists(parent, new_dist);
		lvl_parents = lvl_parents->next;
	}
}
