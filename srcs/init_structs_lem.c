/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs_lem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:15:39 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/03 15:38:14 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

t_lvl		*alloc_new_lvl(void)
{
	t_lvl	*lvl;

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

t_config	*alloc_new_config(void)
{
	t_config	*config;

	if (!(config = (t_config *)easymalloc(sizeof(*config))))
		return (NULL);
	if (!(config->paths = ft_lstnew_head(NULL, NULL)))
		return (NULL);
	config->turns = 0xFFFFFFFF;
	return (config);
}

t_lem		*alloc_new_lem(void)
{
	t_lem	*lem;

	if (!(lem = (t_lem *)easymalloc(sizeof(*lem))))
		return (NULL);
	if (!(lem->paths = ft_lstnew_head(NULL, NULL)))
		return (NULL);
	if (!(lem->table = ft_hash_new_table()))
		return (0);
	lem->table->free_func = &free_table_room;
	lem->shortest = 0xFFFFFFFF;
	lem->max_dist = 0xFFFFFFFF;
	lem->max_paths = 0xFFFFFFFF;
	lem->turns = 0xFFFFFFFF;
	return (lem);
}
