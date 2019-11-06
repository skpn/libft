/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:05:02 by sikpenou          #+#    #+#             */
/*   Updated: 2019/11/06 12:56:08 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lem_in.h"

t_path	*new_path(void)
{
	t_path	*path;

	if (!(path = (t_path *)easymalloc(sizeof(*path))))
		return (0);
	ft_memset(path, 0, sizeof(*path));
	if (!(path->rooms = ft_lstnew_head(NULL, NULL)))
		return (0);
	return (path);
}

t_room	*new_room(void)
{
	t_room			*room;

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

int		init_lem_struct(t_lem **lem)
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

int		main(void)
{
	t_lem	*lem;

	if (!(init_lem_struct(&lem)))
		return (exit_lem(lem, "init failed\n", 1));
	PRINTPOSN;
	if (!parse_input(lem))
		return (exit_lem(lem, "ERROR", 2));
	PRINTPOSN;
	if (!set_graph(lem))
	{
		printf("BEFORE EXIT, ROOMS:\n");
		print_rooms(lem->rooms);
		return (exit_lem(lem, "ERROR", 2));
	}
	PRINTPOSN;
//	print_lem(lem, "ar");
	return (0);
}
