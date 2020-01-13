/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_rooms_paths_lem.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:17:42 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/11 18:12:59 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

void	print_relatives(t_room *room)
{
	t_lst	*elem;
	t_room	*child;

	elem = room->parents->first;
	ft_printf("\tparents: ");
	while (elem)
	{
		child = elem->content;
		ft_printf("%s (d %u, w %u) -- ", child->name, child->dist, child->walk);
		elem = elem->next;
	}
	ft_printf("\n");
	elem = room->children->first;
	ft_printf("\tchildren: ");
	while (elem)
	{
		child = elem->content;
		ft_printf("%s (d %u, w %u) -- ", child->name, child->dist, child->walk);
		elem = elem->next;
	}
}

int		print_room_elem(t_h_elem *room_h_elem)
{
	t_room	*room;

	room = room_h_elem->content;
	printf("PRINT ROOM ELEM FDP\n");
	print_room(room);
	return (1);
}

void	print_room(t_room *room)
{
	if (DEBUG == 0)
		return ;
	ft_printf("PRINTING ROOM\n");
	ft_printf("room '%s': %p\n", room->name, room);
	ft_printf("\tdist %u\n", room->dist);
	ft_printf("\twalk %u\n", room->walk);
	print_relatives(room);
	ft_printf("\n");
}

void	print_path(t_path *path)
{
	t_lst	*path_rooms;
	t_room	*room;

	if (DEBUG == 0)
		return ;
	ft_printf("PRINTING PATH\n");
	path_rooms = path->rooms->first;
	ft_printf("path->size = %u, load = %u /// ", path->rooms->size, path->load);
	while (path_rooms)
	{
		room = path_rooms->content;
		ft_printf("%s (d %u, w %u) -- ", room->name, room->dist, room->walk);
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

void	print_lem(t_lem *lem, char *args)
{
	if (DEBUG == 0)
		return ;
	ft_printf("PRINTING LEM\n");
	if (!args)
		args = "";
	ft_printf("---\nLEM\n---\n");
	ft_printf("nb_ants   : %u\n", lem->nb_ants);
	ft_printf("nb_rooms  : %u\n", lem->nb_rooms);
	ft_printf("max_paths : %u\n", lem->max_paths);
	ft_printf("shortest  : %u\n", lem->shortest);
	ft_printf("max_dist  : %u\n", lem->max_dist);
}