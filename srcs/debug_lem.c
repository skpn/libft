/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:50:50 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/14 17:03:51 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

#define PARENTS 1
#define CHILDREN 2
#define FAMILY 3

void	print_room(t_room *room)
{
	t_lst	*elem;
	t_room	*child;

	if (DEBUG == 0)
		return ;
	printf("PRINTING ROOM\n");
	printf("room '%s': %p\n", room->name, room);
	printf("\tdist %u\n", room->dist);
	printf("\thas_lvl %u\n", room->has_lvl);
	printf("\twalk %u\n", room->walk);
	elem = room->parents->first;
	printf("\tparents: ");
	while (elem)
	{
		child = elem->content;
		printf("%s (d %u, w %u) -- ", child->name, child->dist, child->walk);
		elem = elem->next;
	}
	printf("\n");
	elem = room->children->first;
	printf("\tchildren: ");
	while (elem)
	{
		child = elem->content;
		printf("%s (%u) -- ", child->name, child->dist);
		elem = elem->next;
	}
	printf("\n");
}

void	print_rooms(t_head *rooms)
{
	t_lst	*rooms_lst;

	if (DEBUG == 0)
		return ;
	printf("PRINTING ALL ROOMS\n");
	if (!(rooms_lst = rooms->first))
	{
		printf("no rooms\n");
		return ;
	}
	while (rooms_lst)
	{
		print_room(rooms_lst->content);
		printf("\n");
		rooms_lst = rooms_lst->next;
	}
}

void	print_lvl(t_lvl *lvl)
{
	if (DEBUG == 0)
		return ;
	printf("PRINTING LVL\n");
	printf("lvl %u:\n", lvl->dist);
	print_rooms(lvl->rooms);
}

void	print_anthill(char *anthill)
{
	if (DEBUG == 0)
		return ;
	printf("PRINTING ANTHILL\n");
	printf("anthill:\n---\n'%s'\n---\n", anthill);
}

void	print_path(t_path *path)
{
	t_lst	*path_rooms;

	if (DEBUG == 0)
		return ;
	printf("PRINTING PATH\n");
	printf("path address = %p\n", path);
	path_rooms = path->rooms->first;
	printf("path->turn = %u, path->room->size = %u\n", path->turns, path->rooms->size);
	while (path_rooms)
	{
		printf("%s -- ", ((t_room *)path_rooms->content)->name);
		path_rooms = path_rooms->next;
	}
	printf("\n");
}

void	print_paths(t_head *paths)
{
	t_lst		*path_list;
	unsigned	nb_paths;

	if (DEBUG == 0)
		return ;
	printf("PRINTING ALL PATHS\n");
	nb_paths = paths->size;
	path_list = paths->first;
	while (path_list)
	{
		printf("path %u\n", --nb_paths);
		print_path(path_list->content);
		path_list = path_list->next;
	}
}

void	print_config(t_config *config)
{
	if (DEBUG == 0)
		return ;
	printf("PRINTING CONFIG\n");
	printf("config turns   : %u\n", config->turns);
	printf("config nb_paths: %u\n", config->paths->size);
	printf("valid paths:\n");
	print_paths(config->paths);
}

void	print_lem(t_lem *lem, char *args)
{
	if (DEBUG == 0)
		return ;
	printf("PRINTING LEM\n");
	if (!args)
		args = "";
	printf("---\nLEM\n---\n");
	printf("nb_ants   : %zu\n", lem->nb_ants);
	printf("nb_rooms  : %u\n", lem->nb_rooms);
	printf("max_paths : %u\n", lem->max_paths);
	printf("shortest  : %u\n", lem->shortest);
	printf("max_dist  : %u\n", lem->max_dist);
	if (ft_strchr_pos(args, 'a'))
		print_anthill(lem->anthill);
}
