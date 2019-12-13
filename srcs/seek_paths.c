/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:36:21 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/13 17:49:04 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

/*
5 parties principales:
	- trouver les chemins
		- partir de start, lancer get next room, ajouter la room au chemin
		- si on arrive a end on ajoute le chemin
		- si on croise un chemin on l'enleve de la config
	- ajouter un chemin a une config
		- on ajoute le chemin a la liste de chemins de la config via une
			fonction de tri par insertion
	- enlever un chemin a une config
		- on poppe le chemin de la liste de chemins de la config
	- ajouter une config
		- on realise une copie de la derniere config validee et on l'ajoute
			a la liste de configs de lem
	- remplacer une config (si on obtient une config avec le meme nombre de
		chemins, mais un nombre de tours inferieur, on remplace la config
		la plus lente par la nouvelle)
		- on poppe l'ancienne config de la liste de configs de lem, on la
			free, et on ajoute la nouvelle config a la liste de configs
*/

void	check_room(t_room *child, t_room **next_room)
{
	printf("child = %p, (*next_room) = %p\n", child, (*next_room));
	if (!(*next_room))
	{
		(*next_room) = child;
		printf("child = %p, (*next_room) = %p\n", child, (*next_room));
	}
	else if (child->walk < (*next_room)->walk
		|| (child->walk == (*next_room)->walk && child->dist < (*next_room)->dist))
	{
		(*next_room) = child;
	}
	printf("child = %p, (*next_room) = %p\n", child, (*next_room));
}

t_room	*get_next_room(t_lem *lem, t_path *path, t_room *room, int opt)
{
	t_room	*next_room;
	t_lst	*child;
	t_room	*child_room;

	PRINTPOSN;
	print_room(room);
	next_room = NULL;
	child = opt == CHILD ? room->children->first : room->parents->first;
	PRINTPOSN;
	while (child)
	{
		PRINTPOSN;
		child_room = child->content;
		printf("Testing room's child : \n");
		print_room(child_room);
		if (child_room->dist <= lem->max_dist && child_room->current_path != path)
		{
			PRINTPOSN;
			check_room(child_room, &next_room);
			printf("child_room = %p, next_room = %p\n", child_room, next_room);
			printf("In while next room = \n");
			print_room(next_room);
		}
		child = child->next;
	}
	PRINTPOSN;
	printf("After while next room = \n");
	print_room(next_room);
	if (opt == PARENT && !next_room)
		return (get_next_room(lem, path, room, CHILD));
	PRINTPOSN;
	return (next_room);
}

int		try_path(t_lem *lem, t_path **path)
{
	t_room	*room;

	PRINTPOSN;
	if (!(*path = alloc_new_path()))
		return (0);
	PRINTPOSN;
	if (!ft_lstadd_new((*path)->rooms, lem->end))
		return (0);
	PRINTPOSN;
	lem->end->current_path = *path;
	room = get_next_room(lem, *path, lem->end, PARENT);
	PRINTPOSN;
	while ((room = get_next_room(lem, *path, room, PARENT)))
	{
		PRINTPOSN;
		if (!ft_lstadd_new((*path)->rooms, room))
			return (0);
		PRINTPOSN;
		room->current_path = *path;
		if (room == lem->start)
			return (1);
		PRINTPOSN;
	}
	PRINTPOSN;
	free_path(path);
	PRINTPOSN;
	return (-1);
}

int		seek_paths(t_lem *lem)
{
	t_path		*path;
	int			check_alloc;
	unsigned	max_walk;

	PRINTPOSN;
	path = NULL;
	lem->walk_limit = 1;
	while ((max_walk = get_max_walk(lem)) < lem->walk_limit)
	{
		PRINTPOSN;
		if (!(check_alloc = try_path(lem, &path)))
			return (0);
		else if (check_alloc == 1)
		{
			if (!manage_valid_path(lem, path))
				return (0);
			lem->walk_limit = max_walk + 2;
		}
	}
	PRINTPOSN;
	return (1);
}
