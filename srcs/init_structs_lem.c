/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs_lem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:15:39 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/14 22:35:24 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

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
	room->dist = 0xFFFFFFFF;
	if (!(room->parents = ft_lstnew_head(NULL, NULL)))
		return (NULL);
	if (!(room->children = ft_lstnew_head(NULL, NULL)))
		return (NULL);
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

t_display	*alloc_new_display(unsigned total_rooms)
{
	t_display	*display;
	unsigned	cell;

	if (!(display = (t_display *)easymalloc(sizeof(*display))))
		return (NULL);
	if (!(display->ants_tab = (t_ant **)easymalloc(sizeof(t_ant *) * (total_rooms + 1))))
		return (NULL);
	display->last_id = 1;
	cell = 0;
	while (cell < total_rooms)
	{
		if (!(display->ants_tab[cell] = (t_ant *)easymalloc(sizeof(t_ant))))
			return (NULL);
		cell++;
	}
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
	lem->max_dist = 0xFFFFFFFF;
	lem->max_paths = 0xFFFFFFFF;
	lem->turns = 0xFFFFFFFF;
	return (lem);
}
