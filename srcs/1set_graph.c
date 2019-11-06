/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:18:45 by sikpenou          #+#    #+#             */
/*   Updated: 2019/11/02 14:25:39 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

#define BAD_GRAPH 0
#define OK 1
t_lst	*get_next_lvl(t_lst *lvl)
{
	t_room	*room;
	t_lst	*children;
	t_room	*child;
	t_lst	*next_lvl;

	next_lvl = NULL;
//	printf("CREATING NEW LVL\n");
	while (lvl && (room = lvl->content))
	{
//		printf("checking ");
//		print_rooms(room->children, "ndh", 0);
		children = room->children;
		while (children && (child = children->content))
		{
			if (!child->has_lvl)
			{
//				printf("adding ");
//				print_room(child, "nd", 1);
				child->has_lvl = 1;
				ft_lstadd_new(&next_lvl, children->content);
			}
//			else
//			{
//				printf("not adding ");
//				print_room(child, "nd", 1);
//			}
			children = children->next;
		}
		lvl = lvl->next;
	}
	ft_lstclr(&lvl, LINKS);
	return (next_lvl);
}

unsigned	set_dist(t_lst *children, unsigned dist)
{
	t_room		*child;
	unsigned	size;

	printf("SETTING DIST\n");
	size = 0;
	while (children && (child = children->content))
	{
		if (child->dist > dist)
		{
			child->dist = dist + 1;
			print_room(child, "nd", 0);
			size++;
		}
		children = children->next;
	}
	return (size);
}

void	set_family(t_lem *lem, t_room *parent, t_lst **children)
{
	t_lst	*transfer;
	t_room	*child;

	child = (*children)->content;
	printf("line %d, (*children) of ", __LINE__); print_room(parent, "n", 1);
	print_rooms((*children), "n", 0);
	printf("\nSETTING RELATION OF\n");
	print_room(child, "ndp", 1);
	if (child && parent->dist <= child->dist)
	{
		printf("\npopping ");
		print_room(parent, "n", 0);
		printf("from (*children) of ");
		print_room(child, "n", 1);
		print_rooms(child->children, "n", 0);
	printf("line %d, (*children) of ", __LINE__); print_room(parent, "n", 1);
	print_rooms((*children), "n", 0);
  		transfer = ft_lstpop(&child->children, parent);
//		printf("transfer: %p\n", transfer);
		printf("adding ");
		print_room(transfer->content, "nd", 0);
		printf(" to ");
		print_room(child, "np", 0);
		fflush(0);
	printf("line %d, (*children) of ", __LINE__); print_room(parent, "n", 1);
	print_rooms((*children), "n", 0);
		if (transfer->content != lem->end)
	  		ft_lstadd(&child->parents, transfer);
	printf("line %d, (*children) of ", __LINE__); print_room(parent, "n", 1);
	print_rooms((*children), "n", 0);
		if (parent->dist == child->dist)
		{
			printf("popping_child_to_parent_list\n");
	printf("line %d, (*children) of ", __LINE__); print_room(parent, "n", 1);
	print_rooms((*children), "n", 0);
			transfer = ft_lstpop(&parent->children, child);
	printf("line %d, (*children) of ", __LINE__); print_room(parent, "n", 1);
	print_rooms((*children), "n", 0);
			if (transfer->content != lem->end)
				ft_lstadd(&parent->parents, transfer);
	printf("line %d, (*children) of ", __LINE__); print_room(parent, "n", 1);
	print_rooms((*children), "n", 0);
		}
		print_room(parent, "n", 0);
		printf(" updated ");
		print_room(parent, "c", 0);
		print_room(child, "n", 0);
		printf(" updated  ");
		print_room(child, "c", 0);
		print_room(child, "n", 0);
		printf(" updated  ");
		print_room(child, "p", 0);
	}
	printf("line %d, (*children) of ", __LINE__); print_room(parent, "n", 1);
	print_rooms((*children), "n", 0);
	if (child == lem->end)
	{
		lem->max_dist = lem->nb_ants + child->dist - 1;
		lem->shortest = child->dist;
		printf("room 'end', shortest set to %u, max len set to %u\n"
			, lem->shortest, lem->max_dist);
	}
	printf("line %d, (*children) of ", __LINE__); print_room(parent, "n", 1);
	print_rooms((*children), "n", 0);
}

unsigned	set_children(t_lem *lem, t_lst *lvl)
{
	t_lst		*elem;
	t_room		*parent;
	t_lst		*children;
	unsigned	size;

	size = 0;
	elem = lvl;
	while (elem && (parent = elem->content))
	{
		size += set_dist(parent->children, parent->dist);
		elem = elem->next;
	}
	printf("printing dist of rooms in level\n");
	print_rooms(lvl, "nd", 0);
	while (lvl && (parent = lvl->content))
	{
		printf("SETTING CHILDREN OF ");
		print_room(parent, "ndc", 1);
		printf("\n");
		children = parent->children;
		while (children)
		{
			set_family(lem, parent, &children);
			printf("REMAINING CHILDREN TO CHECK ");
			print_room(parent, "n", 1);
			print_rooms(children, "nd", 0);
			children ? (children = children->next) : 0;
		}
		lvl = lvl->next;
	}
//	printf("out set children, size of lvl %u: %u\n", parent->dist + 1, size);
	return (size);
}

int		set_lvls(t_lem *lem, t_lst *lvl)
{
	unsigned	dist;
	unsigned	next_lvl_size;

	dist = 1;

//	printf("SETTING LVLS\n");
	while (dist < lem->max_dist)
	{
		printf("\n\nstart of while, setting ");
		print_lvl(lvl, dist - 1);
		if ((next_lvl_size = set_children(lem, lvl)) < lem->max_paths
			&& dist < lem->end->dist)
			lem->max_paths = next_lvl_size;
//		printf("\nafter setting lvl:\n");
//		print_lvl(lvl, dist - 1);
		if (next_lvl_size == 0 && dist > lem->end->dist)
		{
//			printf("next lvl size %u,  dist: %u, lem->end->dist: %u\n"
//				, next_lvl_size, dist, lem->end->dist);
			return (1);
		}
		else if (!(lvl = get_next_lvl(lvl)))
		{
			PRINTPOSN;
			return (0);
		}
//		printf("\nnew lvl: lvl %u\n", dist);
		dist++;
	}
	return (1);
}

int		set_graph(t_lem *lem)
{
	t_lst	*lvl;

	PRINTPOSN;
	if (!(lvl = ft_lstnew(lem->start)))
		return (0);
	lem->start->dist = 0;
	print_lem(lem, "ares");
	if (!(set_lvls(lem, lvl)))
		return (BAD_GRAPH);
	print_lem(lem, "r");
	PRINTPOSN;
	return (OK);
}
