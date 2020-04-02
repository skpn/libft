/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 15:31:01 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/14 19:31:58 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static int		check_room(t_lem *lem, t_room *child, t_room *next_room)
{
	if (child == lem->end || child->active_path == lem->generic_path
		|| child->dist + lem->generic_path_size > lem->current_config->turns)
		return (0);
	if (!next_room)
		return (1);
	if (lem->algo_flip >= 8
		&& ((child->walk << 1) + child->dist <= (next_room->walk << 1)
		+ next_room->dist))
		return (1);
	else if (lem->algo_flip <= 7 && lem->algo_flip >= 4
		&& (child->walk + child->dist <= next_room->walk + next_room->dist))
		return (1);
	else if (lem->algo_flip <= 3
		&& child->walk + 3 * child->dist <= next_room->walk
		+ 3 * next_room->dist)
		return (1);
	return (0);
}

static int		update_room(t_lem *lem, t_room *room)
{
	lem->generic_room_lst = lem->generic_room_lst->prev;
	lem->generic_path_size++;
	room->walk++;
	room->previous_path = room->active_path;
	if (room != lem->start && room != lem->end && room->previous_path)
		room->previous_path->is_dead = 1;
	room->active_path = lem->generic_path;
	if (!lem->generic_room_lst)
	{
		if (!ft_lstadd_new(lem->generic_path->rooms, room))
			return (0);
		lem->generic_room_lst = lem->generic_path->rooms->first;
	}
	else
	{
		lem->generic_room_lst->content = room;
	}
	return (1);
}

/*
** add an algo turn where we don't loop on the parents
*/

static t_room	*get_next_room(t_lem *lem, t_room *room)
{
	t_room	*next_room;
	t_lst	*child_lst;
	t_room	*child;

	next_room = NULL;
	child_lst = room->parents->first;
	while (child_lst)
	{
		child = child_lst->content;
		if (check_room(lem, child, next_room))
			next_room = child;
		child_lst = child_lst->next;
	}
	child_lst = room->children->first;
	while (child_lst)
	{
		child = child_lst->content;
		if (check_room(lem, child, next_room))
			next_room = child;
		child_lst = child_lst->next;
	}
	return (next_room);
}

static void		erase_active_path(t_lem *lem)
{
	t_lst	*room_lst;
	t_room	*room;

	if (!lem->generic_path->rooms->last)
		return ;
	room_lst = lem->generic_path->rooms->last->prev;
	while (room_lst && lem->generic_path_size > 1)
	{
		lem->generic_path_size--;
		room = room_lst->content;
		room_lst = room_lst->prev;
		room->active_path = room->previous_path;
		room->previous_path = NULL;
		if (room->active_path)
			room->active_path->is_dead = 0;
	}
}

int				try_path(t_lem *lem)
{
	t_room		*room;
	unsigned	max_dist;

	max_dist = lem->best_config ? lem->best_config->turns : 0xFFFFFFFF;
	lem->generic_path_size = 1;
	lem->generic_room_lst = lem->generic_path->rooms->last;
	room = lem->end;
	while (lem->generic_path_size < max_dist
		&& (room = get_next_room(lem, room)))
	{
		if (!update_room(lem, room))
			return (0);
		if (room == lem->start)
		{
			lem->start->walk = 0;
			lem->start->active_path = NULL;
			return (1);
		}
	}
	erase_active_path(lem);
	return (-1);
}
