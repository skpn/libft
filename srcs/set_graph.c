/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_graph.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 21:05:19 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/07 22:32:28 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

void		kill_dead_rooms(t_room *dead_room)
{
	t_room	*older_sister;
	t_lst	*popped_room;

	older_sister = dead_room->sisters->first->content;
	popped_room = ft_lstpop(older_sister->sisters, dead_room);
	if (popped_room)
		ft_lstfree_elem(&popped_room, FREE_LINKS);
	if (older_sister->sisters->size == 1)
		kill_dead_rooms(older_sister);
}

static int	add_sisters_to_next_lvl(t_head *rooms, t_head *sisters)
{
	t_lst	*sisters_lst;
	t_room	*sister;

	sisters_lst = sisters->first;
	while (sisters_lst)
	{
		sister = sisters_lst->content;
		sisters_lst = sisters_lst->next;
		if (sister->sisters->size == 1)
			kill_dead_rooms(sister);
		else if (!sister->has_lvl)
		{
			sister->has_lvl = 1;
			if (!(ft_lstadd_new(rooms, sister)))
				return (0);
		}
	}
	return (1);
}

static int	get_next_lvl_rooms(t_lem *lem, t_lvl *lvl)
{
	t_lst	*current_rooms_lst;
	t_lst	*tmp;
	t_room	*current_room;

	(void)lem;
	current_rooms_lst = lvl->rooms->first;
	lvl->rooms->first = NULL;
	lvl->rooms->last = NULL;
	while (current_rooms_lst)
	{
		current_room = current_rooms_lst->content;
		if (!add_sisters_to_next_lvl(lvl->rooms, current_room->sisters))
			return (0);
		tmp = current_rooms_lst;
		current_rooms_lst = current_rooms_lst->next;
		ft_lstfree_elem(&tmp, FREE_LINKS);
	}
	return (1);
}

static int	set_lvls(t_lem *lem, t_lvl *lvl)
{
	unsigned	max_dist;
	t_lst		*end_elem;

	max_dist = 0xFFFFFFFF;
	while (lvl->dist < max_dist && lvl->rooms->first)
	{
		set_next_lvl_dists(lvl);
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
			max_dist = lem->shortest + lem->nb_ants - 1;
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
	if (lem->shortest != lem->end->dist + 1 && lem->end->dist != 1)
	{
		free_lvl(&lvl);
		return (PARSING_ERROR);
	}
	kill_end_unreached_rooms(lem->end);
	free_lvl(&lvl);
	return (1);
}
