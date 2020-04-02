/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs_lem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:15:39 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/02 13:35:59 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

t_lvl		*alloc_new_lvl(void)
{
	t_lvl	*lvl;

	if (!(lvl = (t_lvl *)easymalloc(sizeof(*lvl))))
		return (NULL);
	if (!(lvl->rooms = ft_lstnew_head()))
		return (NULL);
	lvl->dist = 0;
	return (lvl);
}

t_path		*alloc_new_path(void)
{
	t_path	*path;

	if (!(path = (t_path *)easymalloc(sizeof(*path))))
		return (NULL);
	if (!(path->rooms = ft_lstnew_head()))
		return (NULL);
	return (path);
}

t_room		*alloc_new_room(char *name)
{
	t_room	*room;

	if (!(room = (t_room *)easymalloc(sizeof(*room))))
		return (NULL);
	if (!(room->parents = ft_lstnew_head()))
		return (NULL);
	if (!(room->children = ft_lstnew_head()))
		return (NULL);
	room->dist = 0xFFFFFFFF;
	room->name = name;
	return (room);
}

t_config	*alloc_new_config(void)
{
	t_config	*config;

	if (!(config = (t_config *)easymalloc(sizeof(*config))))
		return (NULL);
	if (!(config->paths = ft_lstnew_head()))
		return (NULL);
	config->turns = 0xFFFFFFFF;
	return (config);
}

t_lem		*alloc_new_lem(void)
{
	t_lem	*lem;

	if (!(lem = (t_lem *)easymalloc(sizeof(*lem))))
		return (NULL);
	if (!(lem->paths = ft_lstnew_head()))
		return (NULL);
	if (!(lem->generic_path = alloc_new_path()))
		return (NULL);
	if (!(lem->table = ft_h_alloc_new_table()))
		return (0);
	lem->table->func_free = &free_table_room;
	lem->shortest = 0xFFFFFFFF;
	lem->max_dist = 0xFFFFFFFF;
	lem->turns = 0xFFFFFFFF;
	return (lem);
}
