/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:36:21 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/10 18:15:28 by hehlinge         ###   ########.fr       */
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
	/*
	if (child->walk < next_room->walk || (child->walk == next_room->walk
		&& child->dist < next_room->dist))
	{
		return (child);
	}
	*/
	if (child->walk + child->dist <= next_room->walk + next_room->dist)
	{
		return (child);
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
	t_lst	*child;
	t_room	*child_room;

	next_room = NULL;
	child = room->parents->first;
	while (child)
	{
		child_room = child->content;
		if (child_room->dist + path->rooms->size <= lem->current_config->turns
			&& child_room->current_path != path)
		{
			next_room = check_room(child_room, next_room);
		}
		child = child->next;
	}
	child = room->children->first;
	while (child)
	{
		child_room = child->content;
		if (child_room->dist + path->rooms->size <= lem->current_config->turns
			&& child_room->current_path != path)
		{
			next_room = check_room(child_room, next_room);
		}
		child = child->next;
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
//		room->is_closed = 0;
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

int				reset_room_relaunch(t_h_elem *room_h_elem)
{
	t_room *room;

	//ft_printf("RESET ROOM RELAUNCH FDP\n");
	room = room_h_elem->content;
	room->walk = 0;
	room->current_path = NULL;
	room->previous_path = NULL;
	return (1);
}

int				best_to_final(t_lem *lem)
{
	lem->final_config->turns = lem->best_config->turns;
	ft_lstfree(&lem->final_config->paths, FREE_LINKS, KEEP_HEAD);
	if (!(lem->final_config->paths = ft_lstcpy(lem->best_config->paths)))
		return (0);
	ft_lstfree(&lem->best_config->paths, FREE_LINKS, KEEP_HEAD);
	lem->best_config->turns = 0xFFFFFFFF;
	return (1);
}

int				clean_after_algo(t_lem *lem)
{
	lem->algo_flip++;
	lem->current_config->turns = 0xFFFFFFFF;
	ft_lstfree(&lem->current_config->paths, FREE_LINKS, KEEP_HEAD);
	ft_hash_iter(lem->table, &reset_room_relaunch);
	if (lem->best_config->turns < lem->final_config->turns)
	{
		if (!(best_to_final(lem)))
			return (0);
	}
	return (1);
	//ft_hash_iter(lem->table, &print_room_elem);
}

int				seek_paths(t_lem *lem)
{
	t_path		*path;
	int			check_alloc;
	
	lem->max_lives = lem->end->parents->size + lem->end->dist * lem->nb_tubes;
	if (lem->max_lives > LIVES_UPPER_LIMIT)
		lem->max_lives = LIVES_UPPER_LIMIT;
	else if (lem->max_lives < LIVES_LOWER_LIMIT)
		lem->max_lives = LIVES_LOWER_LIMIT;
	if (!(lem->current_config = alloc_new_config())
		|| !(lem->best_config = alloc_new_config())
		|| !(lem->final_config = alloc_new_config()))
		return (0);
	lem->final_config->turns = 0xFFFFFFFF;
	ft_printf("firs ttrn, current config: %u\n", lem->current_config->turns);
	while (lem->algo_flip < NB_ALGO_LAUNCHS)
	{
		ft_printf("algo_flip = %u\n", lem->algo_flip);
		lem->lives = lem->max_lives;
		path = NULL;
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
		ft_printf("End of turn %u, best_config->turns = %u\n", lem->algo_flip, lem->best_config->turns);
		if (!(clean_after_algo(lem)))
			return (0);
	}
	return (1);
}
