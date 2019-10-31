/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:05:02 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/31 14:21:08 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lem_in.h"

t_path	*new_path(t_lst *rooms)
{
	t_path	*path;

	if (!(path = (t_path *)easymalloc(sizeof(*path))))
		return (0);
	ft_memset(path, 0, sizeof(*path));
	path->rooms = rooms;
	return (path);
}

t_room	*new_room(t_lst *parents, t_lst *children)
{
	t_room			*room;

	if (!(room = (t_room *)easymalloc(sizeof(*room))))
		return (0);
	ft_memset(room, 0, sizeof(*room));
	room->parents = parents;
	room->children = children;
	room->dist = sizeof(long) == 4 ? ~0x80000000L : ~0x8000000000000000L;
	return (room);
}

int		init_lem_struct(t_lem **lem)
{
	if (!(*lem = (t_lem *)easymalloc(sizeof(**lem))))
		return (0);
	ft_memset(*lem, 0, sizeof(**lem));
	(*lem)->max_len = sizeof(long) == 4 ? ~0x80000000L : ~0x8000000000000000L;
	return (1);
}

int		main(void)
{
	t_lem	*lem;

	if (!(init_lem_struct(&lem)))
		return (exit_lem(&lem, "init failed\n", 1));
	if (!parse_input(lem))
		return (exit_lem(&lem, "ERROR", 2));
	if (!set_graph(lem))
		return (exit_lem(&lem, "ERROR", 2));
	print_lem(lem, "ar");
	return (0);
}
