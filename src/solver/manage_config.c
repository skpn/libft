/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 10:27:02 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/02 12:30:11 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	pop_dead_paths(t_config *config)
{
	t_lst	*path_lst;
	t_lst	*dead_path_lst;
	t_path	*path;

	path_lst = config->paths->first;
	while (path_lst)
	{
		path = path_lst->content;
		path_lst = path_lst->next;
		if (path->is_dead)
		{
			dead_path_lst = ft_lstpop(config->paths, path);
			if (dead_path_lst)
				ft_lstfree_elem(&dead_path_lst, FREE_STRUCT);
		}
	}
}

static int	add_path(t_lem *lem, t_path *new_path)
{
	t_lst		*config_path_lst;
	t_lst		*new_path_lst;
	unsigned	new_path_size;

	new_path_size = new_path->rooms->size;
	if (!(new_path_lst = ft_lstnew_elem(new_path)))
		return (0);
	config_path_lst = lem->current_config->paths->first;
	if (!config_path_lst
		|| ((t_path *)config_path_lst->content)->rooms->size < new_path_size)
		ft_lstadd(lem->current_config->paths, new_path_lst);
	else
	{
		while (config_path_lst->next
			&& ((t_path *)config_path_lst->next->content)->rooms->size
				> new_path_size)
			config_path_lst = config_path_lst->next;
		ft_lstinsert(lem->current_config->paths, config_path_lst, new_path_lst
			, AFTER);
	}
	pop_dead_paths(lem->current_config);
	balance_load(lem);
	return (1);
}

void		reset_room(t_lem *lem, t_room *room)
{
	if (lem->algo_flip == EACH
		|| lem->reset_flip == 0 || lem->reset_flip == lem->end->dist
		|| (lem->algo_flip % 4 == DIFF && room->dist != lem->reset_flip)
		|| (lem->algo_flip % 4 == SUP && room->dist > lem->reset_flip)
		|| (lem->algo_flip % 4 == INF && room->dist < lem->reset_flip))
		room->walk = 0;
}

int			reset_upper_graph(t_lem *lem)
{
	unsigned	index;
	t_lst		*index_lst;
	t_room		*room;
	t_h_table	*table;

	lem->reset_flip = (lem->reset_flip + 1) % lem->max_dist;
	index = 0;
	table = lem->table;
	while (index < table->size)
	{
		if (table->array[index].first)
		{
			index_lst = table->array[index].first;
			while (index_lst)
			{
				room = ((t_h_elem *)index_lst->content)->content;
				reset_room(lem, room);
				index_lst = index_lst->next;
			}
		}
		index++;
	}
	return (1);
}

int			manage_valid_path(t_lem *lem)
{
	t_path	*path;

	if (!(path = copy_generic_path(lem)))
		return (0);
	if (!ft_lstadd_new(lem->paths, path))
		return (0);
	if (!add_path(lem, path))
		return (0);
	if (lem->best_config->turns <= lem->current_config->turns)
		return (1);
	if (!update_best_config(lem))
		return (0);
	reset_upper_graph(lem);
	return (1);
}
