/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:36:21 by sikpenou          #+#    #+#             */
/*   Updated: 2019/11/06 12:31:54 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

void	erase_path(t_config *config, t_path *path)
{
	/*
	t_lst	*elem;
	t_room	*room;

	elem = path->rooms->first;
	while (elem)
	{
		room = elem->content;
		room->walk--;
		room->current_path = NULL;
		elem = elem->next;
	}
	*/
	ft_lstpop(config->paths, path);
	config->nb_paths--;
	free_path(&path);
}

void	balance_loads(t_lem *lem, t_config *config)
{
	unsigned	added_turns;
	unsigned	ants;
	unsigned	live_paths;
	t_lst		*path_list;
	t_path		*active_path;

	ants = lem->nb_ants;
	config->turns = 0;
	path_list = config->paths->first;
	live_paths = config->paths->size;
	while (path_list)
	{
		active_path = path_list->content;
		added_turns = (ants - active_path->len - lem->shortest) / live_paths;
		ants -= (live_paths * added_turns);
		config->turns += added_turns;
		active_path->load = config->turns;
		live_paths--;
		path_list = path_list->next;
	}
	config->turns += lem->shortest;
}

int		compare_paths_len(t_lst *current_elem, t_lst *new_elem)
{
	t_path	*current_path;
	t_path	*new_path;

	current_path = current_elem->content;
	new_path = new_elem->content;
	if (current_path->len <= new_path->len)
		return (1);
	return (0);
}

int		update_config(t_lem *lem, t_config *config, t_path *new_path)
{
	t_lst	*elem;

	new_path->len = new_path->rooms->size;
	if (!(elem = ft_lstnew_elem(new_path)))
		return (0);
	ft_lstadd_sorted(config->paths, elem, &compare_paths_len);
	config->nb_paths++;
	balance_loads(lem, config);
	return (1);
}
