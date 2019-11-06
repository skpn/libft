/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_graph.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 21:05:19 by sikpenou          #+#    #+#             */
/*   Updated: 2019/11/03 22:42:32 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

t_lvl	*init_start_lvl(t_room *start)
{
	t_lvl	 *lvl;

	if (!(lvl = (t_lvl *)easymalloc(sizeof(*lvl))))
		return (0);
	if (!(lvl->rooms = ft_lstnew(start)))
		return (0);
	lvl->dist = 0;
	return (lvl);
}

int		check_graph(t_lem *lem)
{
	if (lem->max_paths < 1 || lem->max_paths > lem->nb_rooms)
		return (0);
	if (lem->shortest != lem->end->dist)
		return (0);
	return (1);
}

void	update_lem_info(t_lem *lem, t_lvl *lvl)
{
	unsigned	size;

	if (ft_lstfind(lvl->rooms, lem->end))
	{
		lem->shortest = lvl->dist;
		lem->end->dist = lvl->dist;
		lem->max_dist = lem->shortest + lem->nb_ants - 1;
	}
	size = lvl->rooms->size;
	if (size < lem->max_paths && lvl->dist > 0 && lvl->dist < lem->end->dist)
		lem->max_paths = size;
}

void	get_next_lvl_rooms(t_lvl *lvl)
{
	t_lst	*current_rooms;
	t_room	*parent;

	current_rooms = lvl->rooms->first;
	lvl->rooms->first = NULL;
	lvl->rooms->last = NULL;
	while (current_rooms)
	{
		parent = current_rooms->content;
		ft_lstjoin(lvl->rooms, parent->children);
		current_rooms = current_rooms->next;
	}
}

int		set_graph(t_lem *lem)
{
	t_lvl	*lvl;

	if (!(lvl = init_start_lvl(lem->start)))
		return (0);
	g_ptr = lem;
	lem->start->dist = 0;
	printf("START OF SET GRAPH\n");
	print_lvl(lvl);
	while (lvl->dist < lem->max_dist && lvl->rooms)
	{
		printf("----SETTING LVL %u----\n\n", lvl->dist);
		set_next_lvl_dists(lvl);
		printf("AFTER SETTING DISTS\n");
		print_lvl(lvl);
		set_next_lvl_families(lvl);
		printf("AFTER SETTING FAMILIES\n");
		print_lvl(lvl);
		update_lem_info(lem, lvl);
		printf("AFTER UPDATING LEM:\ncurrent dist: %u\nend->dist: %u\n"
				"lvl->rooms: %p\nmax_dist: %u\nmax_paths: %u\n\n"
			, lvl->dist, lem->end->dist, lvl->rooms, lem->max_dist, lem->max_paths);
		print_rooms(lem->rooms);
		get_next_lvl_rooms(lvl);
		printf("AFTER GETTING NEXT LVL\n");
		print_lvl(lvl);
		print_rooms(lem->rooms);
		lvl->dist++;
		return (0);
	}
	ft_lstprint(lem->rooms, "lem->rooms", 0);
	if (!(check_graph(lem)))
		return (0);
	ft_lstfree_head(&lvl->rooms);
	ft_free((void **)lvl);
	return (1);
}
