/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:36:21 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/14 17:34:18 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

void	check_room(t_room *child, t_room **next_room)
{
	if (!(*next_room))
	{
		(*next_room) = child;
	}
	else if (child->walk < (*next_room)->walk
		|| (child->walk == (*next_room)->walk && child->dist < (*next_room)->dist))
	{
		(*next_room) = child;
	}
}

int		update_room(t_room *room, t_path *path)
{
	room->walk++;
	if (room->current_path)
		room->current_path->is_dead = 1;
	room->current_path = path;
	if (!ft_lstadd_new(path->rooms, room))
	{
		printf("\nERROR ADDING ROOM TO PATH\n");
		return (0);
	}
	return (1);
}

t_room	*get_next_room(t_lem *lem, t_path *path, t_room *room, int opt)
{
	t_room	*next_room;
	t_lst	*child;
	t_room	*child_room;

	printf("\nSEEKING NEXT ROOM OF\n");
	print_room(room);
	next_room = NULL;
	child = opt == CHILD ? room->children->first : room->parents->first;
	while (child)
	{
		child_room = child->content;
		if (child_room->dist <= lem->current_config->turns && child_room->current_path != path)
		{
			check_room(child_room, &next_room);
		}
		child = child->next;
	}
	if (opt == PARENT && !next_room)
		return (get_next_room(lem, path, room, CHILD));
	printf("NEXT ROOM\n");
	print_room(next_room);
	return (next_room);
}

int		try_path(t_lem *lem, t_path **path)
{
	t_room	*room;

	PRINTPOSN;
	if (!(*path = alloc_new_path()))
		return (0);
	if (!ft_lstadd_new((*path)->rooms, lem->end))
		return (0);
	lem->end->current_path = *path;
	room = get_next_room(lem, *path, lem->end, PARENT);
	if (!update_room(room, *path))
		return (0);
	PRINTPOSN;
	while ((room = get_next_room(lem, *path, room, PARENT)))
	{
		if (!update_room(room, *path))
			return (0);
		if (room == lem->start)
		{
			printf("\nCOMPLETE PATH:\n");
			print_path(*path);
			lem->start->walk = 0;
			lem->start->current_path = NULL;
			lem->end->current_path = NULL;
			return (1);
		}
	}
	free_path(path);
	printf("NO PATH FOUND\n");
	return (-1);
}

int		seek_paths(t_lem *lem)
{
	t_path		*path;
	int			check_alloc;

	printf("\n\n-------------------------ALGO START-----------------------\n\n");
	lem->lives = lem->end->parents->size;
	path = NULL;
	if (!(lem->current_config = alloc_new_config()))
		return (0);
	while (lem->lives)
	{
		PRINTPOSN;
		if (!(check_alloc = try_path(lem, &path)))
			return (0);
		else if (check_alloc == 1)
		{
			if (!manage_valid_path(lem, path))
			{
				printf("ERROR FROM MANAGE VALID PATH\n");
				return (0);
			}
		}
		printf("lives: %u, most paths: %u, max paths: %u\n",
			lem->lives, lem->most_paths, lem->max_paths);
	}
	PRINTPOSN;
	return (1);
}
