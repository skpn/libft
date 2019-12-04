/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:50:50 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/04 18:21:17 by sikpenou         ###   ########.fr       */
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

	printf("room '%s': %p\n", room->name, room);
	printf("\tdist %u\n", room->dist);
	printf("\thas_lvl %u\n", room->has_lvl);
	printf("\twalk %u\n", room->walk);
	elem = room->parents->first;
	printf("\tparents: ");
	while (elem)
	{
		child = elem->content;
		printf("%s (%u) -- ", child->name, child->dist);
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
	printf("lvl %u:\n", lvl->dist);
	print_rooms(lvl->rooms);
}

void	print_anthill(char *anthill)
{
	printf("anthill:\n---\n'%s'\n---\n", anthill);
}

void	print_paths(t_head *paths)
{
	t_lst		*path_list;
	t_path		*path_content;
	t_lst		*path_rooms;
	unsigned	nb_paths;

	printf("paths? paths !\n");
	nb_paths = paths->size;
	path_list = paths->first;
	while (path_list)
	{
		path_content = path_list->content;
		path_rooms = path_content->rooms->first;
		printf("path %u\n", --nb_paths);
		while (path_rooms)
		{
			printf("%s -- ", ((t_room *)path_rooms->content)->name);
			path_rooms = path_rooms->next;
		}
		printf("\n");
		path_list = path_list->next;
	}
}

void	print_config(t_config *config)
{
	printf("config turns   : %u\n", config->turns);
<<<<<<< HEAD
	printf("config paths size: %u\n", config->paths->size);
	printf("paths:\n");
=======
	printf("config nb_paths: %u\n", config->nb_paths);
	printf("valid paths:\n");
>>>>>>> 96f7d4e307ecb34585e26d44e0e5cfae627b55ba
	print_paths(config->paths);
}

void	print_lem(t_lem *lem, char *args)
{
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
