/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:36:21 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/13 15:04:21 by hehlinge         ###   ########.fr       */
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

void	check_room(t_room *child, t_room *next_room)
{
	if (!next_room)
		next_room = child;
	else if (child->walk < next_room->walk
		|| (child->walk == next_room->walk && child->dist < next_room->dist))
	{
		next_room = child;
	}
}

t_room	*get_next_room(t_lem *lem, t_path *path, t_room *room, int opt)
{
	t_room	*next_room;
	t_lst	*child;
	t_room	*child_room;

	next_room = NULL;
	child = opt == CHILD ? room->children->first : room->parents->first;
	while (child)
	{
		child_room = child->content;
		if (child_room->dist <= lem->max_dist && child_room->current_path != path)
		{
			check_room(child_room, next_room);
		}
		child = child->next;
	}
	if (opt == PARENT && !next_room)
		return (get_next_room(lem, path, room, CHILD));
	return (next_room);
}

int		try_path(t_lem *lem, t_path *path)
{
	t_room	*room;
	
	if (!(path = alloc_new_path()))
		return (0);
	if (!ft_lstadd_new(path->rooms, lem->end))
		return (0);
	lem->end->current_path = path;
	room = get_next_room(lem, path, lem->end, PARENT);
	while ((room = get_next_room(lem, path, room, PARENT)))
	{
		if (!ft_lstadd_new(path->rooms, room))
			return (0);
		room->current_path = path;
		if (room == lem->start)
			return (1);
	}
	free_path(&path);
	return (-1);
}

int		seek_paths(t_lem *lem)
{
	t_path		*path;
	int			check_alloc;
	unsigned	max_walk;

	path = NULL;
	while ((max_walk = get_max_walk(lem)) < lem->walk_limit)
	{
		if (!(check_alloc = try_path(lem, path)))
			return (0);
		else if (check_alloc == 1)
		{
			if (!manage_valid_path(lem, path))
				return (0);
			lem->walk_limit = max_walk + 2;
		}
	}
	return (1);
}
