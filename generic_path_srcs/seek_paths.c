/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:36:21 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/11 19:49:38 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

void	print_generic_path(t_lem *lem)
{
	t_lst	*path_rooms;
	t_room	*room;

	if (DEBUG == 0)
		return ;
	path_rooms = lem->generic_room_lst;
	//ft_printf("path->size = %u, load = %u /// ", path->rooms->size, path->load);
	while (path_rooms)
	{
		room = path_rooms->content;
//		ft_printf("%s (d %u, w %u) -- ", room->name, room->dist, room->walk);
		path_rooms = path_rooms->next;
		if (room == lem->end)
			break ;
	}
	ft_printf("\n");
}


static int		check_room(t_lem *lem, t_room *child, t_room *next_room)
{
	if (child->active_path == lem->generic_path
		|| child->dist + lem->generic_path_size > lem->current_config->turns)
		return (0);
	if (!next_room)
		return (1);
	if (lem->algo_flip >= 9
		&& ((child->walk << 1) + child->dist <= (next_room->walk << 1)
		+ next_room->dist))
		return (1);
	else if (lem->algo_flip <= 8 && lem->algo_flip >= 4
		&& (child->walk + child->dist <= next_room->walk + next_room->dist))
		return (1);
	else if (lem->algo_flip <= 3
		&&	child->walk + 3 * child->dist <= next_room->walk
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
	{
//		ft_printf("at room '%s', killed path:\n", room->name);
//		print_path(room->previous_path);
		room->previous_path->is_dead = 1;
	}
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

static t_room	*get_next_room(t_lem *lem, t_room *room)
{
	t_room	*next_room;
	t_lst	*child_lst;
	t_room	*child;

	next_room = NULL;
	child_lst = room->parents->first;
//	ft_printf("seeking room with algo flip: %u\n", lem->algo_flip);
//	print_generic_path(lem);
//	print_room(room);
	while (child_lst)
	{
		child = child_lst->content;
//		ft_printf("parent %s active path = %p, path = %p, walk %u\n",
//		child->name, child->active_path, lem->generic_path, child->walk);
		if (check_room(lem, child, next_room))
			next_room = child;
		child_lst = child_lst->next;
	}
	child_lst = room->children->first;
	while (child_lst)
	{
		child = child_lst->content;
//		ft_printf("parent %s active path = %p, path = %p, walk %u\n",
//		child->name, child->active_path, lem->generic_path, child->walk);
		if (check_room(lem, child, next_room))
			next_room = child;
		child_lst = child_lst->next;
	}
//	if (next_room)
//		ft_printf("next room: %s\n", next_room->name);
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

static int		try_path(t_lem *lem)
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
//	ft_printf("\n");
	return (-1);
}

int				reset_room_relaunch(t_h_elem *room_h_elem)
{
	t_room *room;

	////ft_printf("RESET ROOM RELAUNCH FDP\n");
	room = room_h_elem->content;
	room->walk = 0;
	room->active_path = NULL;
	room->previous_path = NULL;
	return (1);
}

int				best_to_final(t_lem *lem)
{
	lem->final_config->turns = lem->best_config->turns;
	ft_lstfree(&lem->final_config->paths, FREE_LINKS, FREE_HEAD);
	if (!(lem->final_config->paths = ft_lstcpy(lem->best_config->paths)))
		return (0);
	return (1);
}

int				clean_after_algo(t_lem *lem)
{
	lem->current_config->turns = 0xFFFFFFFF;
	ft_lstfree(&lem->current_config->paths, FREE_LINKS, KEEP_HEAD);
	ft_hash_iter(lem->table, &reset_room_relaunch);
	if (lem->best_config->turns < lem->final_config->turns)
	{
		if (!(best_to_final(lem)))
			return (0);
	}
	ft_lstfree(&lem->best_config->paths, FREE_LINKS, KEEP_HEAD);
	lem->best_config->turns = 0xFFFFFFFF;
//	ft_hash_iter(lem->table, &print_room_elem);
	return (1);
}

int				set_generic_path(t_lem *lem)
{
	if (!(ft_lstadd_new(lem->generic_path->rooms, lem->end)))
		return (0);
	lem->generic_room_lst = lem->generic_path->rooms->last;
	lem->end->active_path = lem->generic_path;
	lem->generic_path_size++;
	return (1);
}

int				seek_paths(t_lem *lem)
{
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
	if (!set_generic_path(lem))
		return (0);
	while (lem->algo_flip < NB_ALGO_LAUNCHS)
	{
//		POS;
		lem->lives = lem->max_lives;
		lem->reset_flip = 0;
		while (lem->lives)
		{
			lem->lives--;
//		ft_printf("lives: %u\n", lem->lives);
			if (!(check_alloc = try_path(lem)))
				return (0);
			else if (check_alloc == 1)
			{
//	POS;
				if (!manage_valid_path(lem))
					return (0);
//	POS;
			}
//	POS;
		}
		if (!(clean_after_algo(lem)))
			return (0);
		lem->algo_flip++;
	}
	return (1);
}
