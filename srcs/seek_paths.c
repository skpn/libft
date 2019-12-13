/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:36:21 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/13 11:46:01 by hehlinge         ###   ########.fr       */
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

t_config	*copy_config(t_config *original)
{
	t_config	*new_configi;
	t_lst		*

	if (!(new_config = alloc_new_config()))
		return (0);
	if (!(new_config->paths
}

int		sort_cmp(t_lst *to_insert, t_lst *to_compare)
{
	return (((t_path *)to_insert->content)->len
		> ((t_path *)to_compare->content)->len);
}

// ATTENTION LSTADD_SORTED NOT TESTED
int		config_do(int opt, t_lem *lem, t_config *config, t_path *path)
{
	t_lst	*path_elem;

	if (opt == ADD_PATH)
	{
		if (!(path_elem = ft_lstnew_elem(path)))
			return (0);
		ft_lstadd_sorted(config->paths, path_elem, &sort_cmp);
	}
	else if (opt == POP_PATH)
	{
		ft_lstpop(config->paths, path);
		free_path(&path);
	}
	else if (opt == ADD_CONFIG)
	{
		return (copy_config(lem, config));
	}
	else if (opt == DELETE_CONFIG)
	{
		ft_lstpop(lem->config_lst, config);
		free_config(&config);
	}
	return (1);
}

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
	t_room	*child;

	next_room = NULL;
	child = opt == CHILD ? room->children->first : room->parents->first;
	while (child)
	{
		if (child->dist <= lem->max_len && child->current_path != path)
		{
			check_room(child, next_room);
		}
		child = child->next;
	}
	if (opt == PARENT && !next_room)
		return (get_next_room(lem, path, room, CHILD));
	return (next_room);
}

int		try_path(t_lem *lem, t_room *room, t_path *path)
{
	if (!(path = alloc_new_path()))
		return (0);
	if (!ft_lstadd_new(path->rooms, lem->end))
		return (0);
	end->current_path = path;
	while (room = get_next_room(lem, room, PARENT))
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

int			get_max_walk(t_lem *lem)
{
	int		walk;
	t_lst	*parent;

	walk = 0;
	parent = lem->end->parents->first;
	while (parent)
	{
		if (parent->content->walk > walk)
			walk = parent->content->walk;
		parent = parent->next;
	}
	return (walk);
}

int			manage_valid_path(t_lem *lem, t_path *path)
{
	int	walk;

	walk = get_max_walk(lem);
	lem->max_walk = walk + 2;
}

int		seek_paths(t_lem *lem)
{
	t_config	*current_config;
	t_config	*biggest_config;
	t_lst		*parent;
	t_path		*path;
	int			ret;
	
	parent = lem->end->parents->first;
	while (get_max_walk(lem) < lem->max_walk)
	{
		if (!(ret = try_path(lem, parent->content, path)))
			return (0);
		else if (ret == 1)
			manage_valid_path(lem, path);
		parent = parent->next;
		if (!parent)
			parent = lem->end->parents->first;
	}
}
