/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:36:21 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/06 10:49:36 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

static t_room	*check_room(t_room *child, t_room *next_room)
{
	if (!next_room)
	{
		return (child);
	}
	else if (child->walk < next_room->walk
		|| (child->walk == next_room->walk && child->dist < next_room->dist))
	{
		return (child);
	}
	return (next_room);
}

static int		update_room(t_room *room, t_path *path)
{
	room->walk++;
	if (room->current_path)
		room->current_path->is_dead = 1;
	room->current_path = path;
	if (!ft_lstadd_new(path->rooms, room))
		return (0);
	return (1);
}

static t_room	*get_next_room(t_lem *lem, t_path *path, t_room *room)
{
	t_room	*next_room;
	t_lst	*child;
	t_room	*child_room;

	next_room = NULL;
	child = room->parents->first;
	while (child)
	{
		child_room = child->content;
		if (child_room->dist <= lem->current_config->turns
			&& child_room->current_path != path)
		{
			next_room = check_room(child_room, next_room);
		}
		child = child->next;
	}
	return (next_room);
}

static int		try_path(t_lem *lem, t_path **path)
{
	t_room	*room;

	if (!(*path = alloc_new_path()))
		return (0);
	if (!ft_lstadd_new((*path)->rooms, lem->end))
		return (0);
	lem->end->current_path = *path;
	room = get_next_room(lem, *path, lem->end);
	if (!update_room(room, *path))
		return (0);
	while ((room = get_next_room(lem, *path, room)))
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
	free_path(path);
	return (-1);
}

int				seek_paths(t_lem *lem)
{
	t_path		*path;
	int			check_alloc;

	lem->max_lives = lem->end->parents->size + lem->end->dist * lem->nb_tubes;
	if (lem->max_lives > LIVES_LIMIT)
		lem->max_lives = LIVES_LIMIT;
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
