/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:36:21 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/07 21:19:34 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

static t_room	*check_room(t_room *sister, t_room *next_room)
{
	if (!next_room)
	{
		return (sister);
	}
	/*
	if (sister->walk < next_room->walk || (sister->walk == next_room->walk
		&& sister->dist < next_room->dist))
	{
		return (sister);
	}
	*/
	if (sister->walk + sister->dist <= next_room->walk + next_room->dist)
	{
		return (sister);
	}
	return (next_room);
}

static int		update_room(t_room *room, t_path *path)
{
	room->walk++;
	room->previous_path = room->current_path;
	if (room->previous_path)
		room->previous_path->is_dead = 1;
	room->current_path = path;
	if (!ft_lstadd_new(path->rooms, room))
		return (0);
	return (1);
}

static t_room	*get_next_room(t_lem *lem, t_path *path, t_room *room)
{
	t_room	*next_room;
	t_lst	*sister;
	t_room	*sister_room;

	next_room = NULL;
	sister = room->sisters->first;
	while (sister)
	{
		sister_room = sister->content;
		if (sister_room->dist + path->rooms->size <= lem->current_config->turns
			&& sister_room->current_path != path)
		{
			next_room = check_room(sister_room, next_room);
		}
		sister = sister->next;
	}
	return (next_room);
}

static void		erase_current_path(t_path *path)
{
	t_lst	*room_lst;
	t_room	*room;

	room_lst = path->rooms->first;
	while (room_lst)
	{
		room = room_lst->content;
		room_lst = room_lst->next;
		room->current_path = room->previous_path;
		room->previous_path = NULL;
		if (room->current_path)
			room->current_path->is_dead = 0;
	}
}

static int		try_path(t_lem *lem, t_path **path)
{
	t_room		*room;
	unsigned	max_dist;

	max_dist = lem->best_config ? lem->best_config->turns : 0xFFFFFFFF;
	if (!(*path = alloc_new_path()))
		return (0);
	if (!ft_lstadd_new((*path)->rooms, lem->end))
		return (0);
	lem->end->current_path = *path;
	room = get_next_room(lem, *path, lem->end);
	if (!update_room(room, *path))
		return (0);
	while ((*path)->rooms->size < max_dist
		&& (room = get_next_room(lem, *path, room)))
	{
		if (!update_room(room, *path))
			return (0);
		if (room == lem->start)
		{
			lem->start->walk = 0;
			lem->start->current_path = NULL;
			lem->end->current_path = NULL;
			return (1);
		}
	}
	erase_current_path(*path);
	free_path(path);
	return (-1);
}

int				seek_paths(t_lem *lem)
{
	t_path		*path;
	int			check_alloc;

	lem->max_lives = lem->end->sisters->size + lem->end->dist * lem->nb_tubes;
	if (lem->max_lives > LIVES_UPPER_LIMIT)
		lem->max_lives = LIVES_UPPER_LIMIT;
	else if (lem->max_lives < LIVES_LOWER_LIMIT)
		lem->max_lives = LIVES_LOWER_LIMIT;
	lem->lives = lem->max_lives;
	path = NULL;
	if (!(lem->current_config = alloc_new_config())
		|| !(lem->best_config = alloc_new_config()))
		return (0);
	while (lem->lives)
	{
		if (!(check_alloc = try_path(lem, &path)))
			return (0);
		else if (check_alloc == 1)
		{
			if (!manage_valid_path(lem, path))
				return (0);
		}
	}
	return (1);
}
