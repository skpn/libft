/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs_lem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:15:39 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/19 14:32:37 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

t_lvl	*alloc_new_lvl(void)
{
	t_lvl	 *lvl;

	if (!(lvl = (t_lvl *)easymalloc(sizeof(*lvl))))
		return (NULL);
	if (!(lvl->rooms = ft_lstnew_head(NULL, NULL)))
		return (NULL);
	lvl->dist = 0;
	return (lvl);
}

t_path		*alloc_new_path(void)
{
	t_path	*path;

	if (!(path = (t_path *)easymalloc(sizeof(*path))))
		return (NULL);
	if (!(path->rooms = ft_lstnew_head(NULL, NULL)))
		return (NULL);
	return (path);
}

t_room		*alloc_new_room(void)
{
	t_room	*room;

	if (!(room = (t_room *)easymalloc(sizeof(*room))))
		return (NULL);
	if (!(room->parents = ft_lstnew_head(NULL, NULL)))
		return (NULL);
	if (!(room->children = ft_lstnew_head(NULL, NULL)))
		return (NULL);
	room->dist = 0xFFFFFFFF;
	return (room);
}

t_config	*alloc_new_config(int head_opt)
{
	t_config	*config;

	if (!(config = (t_config *)easymalloc(sizeof(*config))))
		return (NULL);
	if (head_opt == WITH_HEAD)
	{
		if (!(config->paths = ft_lstnew_head(NULL, NULL)))
			return (NULL);
	}
	config->turns = 0xFFFFFFFF;
	return (config);
}

t_ant		**alloc_new_ants_tab(unsigned total_rooms)
{
	unsigned	cell;
	t_ant		**ants_tab;

	if (!(ants_tab = (t_ant **)easymalloc(sizeof(t_ant *) * (total_rooms + 1))))
		return (NULL);
	cell = 0;
	while (cell < total_rooms)
	{
		if (!(ants_tab[cell] = (t_ant *)easymalloc(sizeof(t_ant))))
			return (NULL);
		cell++;
	}
	return (ants_tab);
}

t_display	*alloc_new_display(unsigned total_rooms)
{
	t_display	*display;

	if (!(display = (t_display *)easymalloc(sizeof(*display))))
		return (NULL);
	if (!(display->ants_tab = alloc_new_ants_tab(total_rooms)))
		return (NULL);
	display->last_id = 1;
	display->total_rooms = total_rooms;
	return (display);
}

t_lem		*alloc_new_lem(void)
{
	t_lem	*lem;

	if (!(lem = (t_lem *)easymalloc(sizeof(*lem))))
		return (NULL);
	if (!(lem->rooms = ft_lstnew_head(NULL, NULL)))
		return (NULL);
	if (!(lem->config_lst = ft_lstnew_head(NULL, NULL)))
		return (NULL);
	if (!(lem->paths = ft_lstnew_head(NULL, NULL)))
		return (NULL);
	if (!(lem->rooms_table = ft_hash_new_table()))
		return (0);
	tem->rooms_table->free_func = &free_room;
	lem->shortest = 0xFFFFFFFF;
	lem->max_dist = 0xFFFFFFFF;
	lem->max_paths = 0xFFFFFFFF;
	lem->turns = 0xFFFFFFFF;
	return (lem);
}
