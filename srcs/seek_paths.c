<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:36:21 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/04 22:33:19 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
=======
>>>>>>> 96f7d4e307ecb34585e26d44e0e5cfae627b55ba

#include "lem_in.h"
#include "libft.h"

<<<<<<< HEAD
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

int		copy_config(t_lem *lem, t_config *config)
{
	
}

int		config_do(int opt, t_lem *lem, t_lem *config, t_path *path)
{
	if (opt == ADD_PATH)
		ft_lstadd_new(config->paths, path);
	else if (opt == POP_PATH)
	{
		ft_lstpop(config->paths, path);
		free_path(&path);
	}
	else if (opt == ADD_CONFIG)
		return (copy_config(lem, config));
	else if (opt == DELETE_CONFIG)
	{
		ft_lstpop(lem->config_lst, config);
		free_config(&config);
=======
t_room	*get_next_room(t_path *current_path, t_lst *room_list)
{
	t_room	*next;
	t_room	*test;

	next = NULL;
	while (room_list)
	{
		test = room_list->content;
		if (!next || next->walk > test->walk || next->dist > test->dist)
			if (test->current_path != current_path)
				next = test;
		room_list = room_list->next;
	}
	return (next);
}

int		try_path(t_lem *lem, t_path *path, t_room *current)
{
	t_room	*next;

	while (1)
	{
		current->walk++;
		current->current_path = path;
		next = get_next_room(path, current->children->first);
		if (next == NULL)
			return (0);
		else if (next->dist == 0)
			return (1);
		if (path->rooms->size == lem->max_dist)
			return (0);
		if (!(ft_lstadd_new(path->rooms, current)))
			return (0);
		current = next;
	}
}

int		seek_paths(t_lem *lem)
{
	t_path	*test_path;
	t_room	*start_room;

	if (!(test_path = new_path()))
		return (0);
	while (lem->config->nb_paths < lem->max_paths)
	{
		start_room = get_next_room(NULL, lem->start->children->first);
		if (!start_room)
			return (0);
		if (try_path(lem, test_path, start_room) == 1)
		{
			if (update_config(lem, lem->config, test_path) == 0)
				return (0);
			if (!(test_path = new_path()))
				return (0);
		}
		else
		{
			ft_lstfree(&test_path->rooms, FREE_LINKS, KEEP_HEAD);
		}
>>>>>>> 96f7d4e307ecb34585e26d44e0e5cfae627b55ba
	}
	return (1);
}
