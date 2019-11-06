/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:18:45 by sikpenou          #+#    #+#             */
/*   Updated: 2019/11/01 19:06:08 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

#define BAD_GRAPH 0
#define OK 1
void	set_parents(t_lst *current_lvl)
{
	t_lst	*elem;
	t_room	*parent;
	t_lst	*child_elem;
	t_room	*child;
	t_lst	*transfer;

	PRINTPOSN;
	elem = current_lvl;
	printf("setting parents for lvl %lu\n", ((t_room *)elem->content)->dist);
	while (elem && (parent = elem->content))
	{
		child_elem = parent->children;
			print_room(parent, "nadwf", 0);
		while (child_elem && (child = child_elem->content))
		{
			print_room(parent, "nadwf", 0);
			print_room(child, "nadwf", 0);
			if (child->dist <= parent->dist)
			{
				transfer = ft_lstpop(&parent->children, child_elem);
				if (transfer)
				{
					printf("popping ");
					print_room(transfer->content, "n", 0);
					printf("to ");
					print_room(parent, "n", 0);
				}
				ft_lstadd(&parent->parents, transfer);
			}
			child_elem = child_elem->next;
		}
			print_room(parent, "nadwf", 0);
		elem = elem->next;
	}
	printf("\nafter setting parents: ");
	print_lvl(current_lvl, parent->dist);
}

long	set_next_lvl(t_lem *lem, t_lst *next_lvl, long dist)
{
	t_lst	*elem;
	t_room	*room;
	long	ctr;

	PRINTPOSN;
	elem = next_lvl;
	ctr = 0;
	while (elem && (room = elem->content))
	{
		if (room->dist > dist)
			room->dist = dist;
		if (room == lem->end && lem->nb_paths == 0)
		{
			lem->shortest = dist;
			lem->max_dist = lem->shortest + lem->nb_ants -1;
			lem->nb_paths = 1;
		}
		elem = elem->next;
		++ctr;
	}
	printf("\nlvl %ld has been set: \n", dist);
	print_lvl(next_lvl, dist);
	return (ctr);
}

t_lst	*get_next_lvl(t_lst *current_lvl)
{
	t_lst	*elem;
	t_room	*room;
	t_lst	*next_lvl;

	PRINTPOSN;
	next_lvl = NULL;
	elem = current_lvl;
	printf("\ncurrent lvl: ");
	print_lvl(current_lvl, ((t_room *)elem->content)->dist);
	while (elem && (room = elem->content))
	{
		print_room(room, "nadwf", 0);
		next_lvl = ft_lstjoin(room->children, next_lvl);
		elem = elem->next;
	}
	printf("\nnext lvl: %p\n", next_lvl);
	print_lvl(next_lvl, room->dist + 1);
	return (next_lvl);
}

int		set_lvl(t_lem *lem, t_lst *current_lvl, t_lst *next_lvl)
{
	long unsigned	dist;
	long unsigned	ctr;

	dist = 1;
	while (dist < lem->max_dist)
	{
		printf("start of while, ");
		print_rooms_addr(lem->rooms);
		print_lvl(current_lvl, dist - 1);
		if (!(next_lvl = get_next_lvl(current_lvl)))
		{
			PRINTPOSN;
			return (0);
		}
		if (!(next_lvl->content) && lem->nb_paths == 0)
		{
			PRINTPOSN;
			return (0);
		}
		if ((ctr = set_next_lvl(lem, next_lvl, dist))
				&& ctr < lem->max_paths)
		{
			PRINTPOSN;
			lem->max_paths = ctr;
		}
		else if (!ctr && lem->nb_paths == 0)
		{
			PRINTPOSN;
			return (0);
		}
		set_parents(current_lvl);
		ft_lstclr(&current_lvl, LINKS);
		current_lvl = next_lvl;
		dist++;
	}
	return (1);
}

int		set_graph(t_lem *lem)
{
	t_lst	*current_lvl;

	if (!(current_lvl = ft_lstnew(NULL, 0)))
		return (0);
	lem->start->dist = 0;
	current_lvl->content = lem->start;
	print_lem(lem, "ares");
	if (!(set_lvl(lem, current_lvl, NULL)))
		return (BAD_GRAPH);
	return (OK);
}
