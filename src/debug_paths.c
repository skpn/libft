/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 12:04:32 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/13 12:07:58 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

void	print_path(t_path *path)
{
	t_lst	*path_rooms;
	t_room	*room;

	if (DEBUG == 0)
		return ;
	path_rooms = path->rooms->first;
	ft_printf("path->size = %u, load = %u /// ", path->rooms->size, path->load);
	while (path_rooms)
	{
		room = path_rooms->content;
		ft_printf("%s -- ", room->name);
		path_rooms = path_rooms->next;
	}
	ft_printf("\n");
}

void	print_paths(t_head *paths)
{
	t_lst		*path_list;

	if (DEBUG == 0)
		return ;
	ft_printf("PRINTING ALL PATHS\n");
	path_list = paths->first;
	while (path_list)
	{
		print_path(path_list->content);
		path_list = path_list->next;
	}
}

void	print_generic_path(t_lem *lem)
{
	t_lst	*path_rooms;
	t_room	*room;

	if (DEBUG == 0)
		return ;
	path_rooms = lem->generic_room_lst;
	while (path_rooms)
	{
		room = path_rooms->content;
		path_rooms = path_rooms->next;
		if (room == lem->end)
			break ;
	}
	ft_printf("\n");
}
