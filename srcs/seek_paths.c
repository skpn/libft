/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:36:21 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/07 10:57:39 by sikpenou         ###   ########.fr       */
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
	if (path->rooms->size > 1)
		((t_room *)path->rooms->last->prev->content)->is_closed = 1;
	return (1);
}

// ex: current_config->turns = 4, if child->dist > 4 we skip it
static t_room	*get_next_room(t_lem *lem, t_path *path, t_room *room)
{
	t_room	*next_room;
	t_lst	*children_lst;
	t_room	*child;

	(void)lem;
	next_room = NULL;
	children_lst = room->parents->first;
	while (children_lst)
	{
		child = children_lst->content;
		if (child->current_path != path && !child->is_closed)
		{
			next_room = check_room(child, next_room);
		}
		children_lst = children_lst->next;
	}
	children_lst = room->children->first;
	while (children_lst)
	{
		child = children_lst->content;
		if (child->current_path != path && !child->is_closed)
		{
			next_room = check_room(child, next_room);
		}
		children_lst = children_lst->next;
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
		room->current_path = NULL;
		room->is_closed = 0;
	}
}

void			unprotect_rooms(t_config *config)
{
	t_lst	*path_elem;
	t_path	*path;
	t_lst	*room_elem;
	t_room	*room;

	path_elem = config->paths->first;
	while (path_elem)
	{
		path = path_elem->content;
		room_elem = path->rooms->first;
		ft_printf("Unprotecting paths, room->is_closed = %u\n", ((t_room *)room_elem->content)->is_closed);
		while (room_elem)
		{
			room = room_elem->content;
			room->is_closed = 0;
			room_elem = room_elem->next;
		}
		path_elem = path_elem->next;
	}
}

static int		try_path(t_lem *lem, t_path **path, t_room *room)
{
	if (!(*path = alloc_new_path()))
		return (0);
	if (!ft_lstadd_new((*path)->rooms, lem->end))
		return (0);
	lem->end->current_path = *path;
	//room = get_next_room(lem, *path, lem->end);
	if (!update_room(room, *path))
		return (0);
	while ((room = get_next_room(lem, *path, room)))
	{
		//ft_printf("next room:\n");
		//print_room(room);
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
	t_lst		*end_parent;

	lem->max_lives = lem->end->parents->size + lem->end->dist * lem->nb_tubes;
	if (lem->max_lives > LIVES_UPPER_LIMIT)
		lem->max_lives = LIVES_UPPER_LIMIT;
	else if (lem->max_lives < LIVES_LOWER_LIMIT)
		lem->max_lives = LIVES_LOWER_LIMIT;
	lem->lives = lem->max_lives;
	if (!(lem->current_config = alloc_new_config())
		|| !(lem->best_config = alloc_new_config()))
		return (0);
	while (lem->lives && end_parent)
	{
		if (!(check_alloc = try_path(lem, &path)))
			return (0);
		else if (check_alloc == 1)
		{
			lem->loop_limit = end_parent;
			if (!manage_valid_path(lem, path))
				return (0);
		}
		end_parent = get_next_end_parent(lem, end_parent);
	}
	return (1);
}
