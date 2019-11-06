/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_lvl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 22:11:27 by sikpenou          #+#    #+#             */
/*   Updated: 2019/11/03 11:02:58 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

void	set_children_dists(t_room *parent)
{
	t_lst	*children;
	t_room	*child;

	children = parent->children;
	while (children)
	{
		child = children->content;
		if (child->dist > parent->dist)
			child->dist = parent->dist + 1;
		children = children->next;
	}
}

void	set_parent_as_parent(t_room *parent, t_room *child, char *opt)
{
	t_lst	*transfer;

	if (!ft_strcmp(opt, "parent"))
	{
		transfer = ft_lstpop(&child->children, parent);
		ft_lstadd(&child->parents, transfer);
	}
}

void	set_parent_as_brother(t_room *parent, t_room *child, char *opt)
{
	t_lst	*transfer;

	if (!ft_strcmp(opt, "brother"))
	{
		transfer = ft_lstpop(&child->children, parent);
		ft_lstadd(&child->parents, transfer);
		transfer = ft_lstpop(&parent->children, child);
		ft_lstadd(&parent->parents, transfer);
	}
}

void	set_parent_as_child(t_room *parent, t_room *child, char *opt)
{
	t_lst	*transfer;

	if (!ft_strcmp(opt, "child"))
	{
		transfer = ft_lstpop(&parent->children, child);
		ft_lstadd(&parent->parents, transfer);
	}
}

void	set_children_families(t_room *parent)
{
	t_lst	*children;
	t_room	*child;

	children = parent->children;
	while (children)
	{
		child = children->content;
		if (child->dist > parent->dist)
			set_parent_as_parent(parent, child, "parent");
		else if (child->dist == parent->dist)
			set_parent_as_brother(parent, child, "brother");
		else
			set_parent_as_child(parent, child, "child");
		children = children->next;
	}
}

void	set_next_lvl(t_lst *rooms, char *opt)
{
	t_room		*parent;

	while (rooms)
	{
		parent = rooms->content;
		if (!ft_strcmp(opt, "dists"))
			set_children_dists(parent);
		else if (!ft_strcmp(opt, "families"))
			set_children_families(parent);
		rooms = rooms->next;
	}
}

void	get_next_lvl_rooms(t_lvl *lvl)
{
	t_lst	*elem;
	t_room	*room;
	t_lst	*next_lvl_rooms;

	next_lvl_rooms = NULL;
	printf("%s %d, lem address: %p\n", __func__, __LINE__, g_ptr);
	elem = lvl->rooms;
	while (elem)
	{
		room = elem->content;
		next_lvl_rooms = ft_lstjoin(next_lvl_rooms, room->children);
		elem = elem->next;
	}
	ft_lstclr(&lvl->rooms, LINKS);
	lvl->rooms = next_lvl_rooms;
	printf("after join, lvl rooms:\n");
	ft_lstprint(lvl->rooms, "lvl->rooms", 0);
}

