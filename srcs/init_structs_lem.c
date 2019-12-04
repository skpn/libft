/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs_lem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:15:39 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/04 22:33:22 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

t_path		*alloc_new_path(void)
{
	t_path	*path;

	if (!(path = (t_path *)easymalloc(sizeof(*path))))
		return (0);
	ft_memset(path, 0, sizeof(*path));
	if (!(path->rooms = ft_lstnew_head(NULL, NULL)))
		return (0);
	return (path);
}

t_room		*alloc_new_room(void)
{
	t_room	*room;

	if (!(room = (t_room *)easymalloc(sizeof(*room))))
		return (0);
	ft_memset(room, 0, sizeof(*room));
	room->dist = 0xFFFFFFFF;
	if (!(room->parents = ft_lstnew_head(NULL, NULL)))
		return (0);
	if (!(room->children = ft_lstnew_head(NULL, NULL)))
		return (0);
	printf("room malloc at address: %p\n", room);
	return (room);
}

t_config	*alloc_new_config(void)
{
	t_config	*config;

	if (!(config = (t_config *)easymalloc(sizeof(*config))))
		return (0);
	ft_memset(config, 0, sizeof(*config));
	if (!(config->paths = ft_lstnew_head(NULL, NULL)))
		return (0);
	return (config);
}

int			init_lem(t_lem **lem)
{
	if (!(*lem = (t_lem *)easymalloc(sizeof(**lem))))
		return (0);
	ft_memset(*lem, 0, sizeof(**lem));
	if (!((*lem)->rooms = ft_lstnew_head(NULL, NULL)))
		return (0);
	(*lem)->max_dist = 0xFFFFFFFF;
	(*lem)->max_paths = 0xFFFFFFFF;
	return (1);
}
