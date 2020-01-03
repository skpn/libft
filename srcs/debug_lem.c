/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_lem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 20:38:01 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/03 11:05:50 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

#define PARENTS 1
#define CHILDREN 2
#define FAMILY 3

void	print_display(t_display *display)
{
	if (DEBUG == 0)
		return ;
	ft_printf("PRINTING DISPLAY\n");
	ft_printf("last id    : %u\n", display->last_id);
	ft_printf("turn       : %u\n", display->turn);
	ft_printf("lem->turns : %u\n", display->lem_turns);
	ft_printf("total rooms: %u\n", display->total_rooms);
	ft_printf("nb_ants    : %u\n", display->nb_ants);
}

void	print_ants_tab(t_ant **tab)
{
	unsigned	cell;

	if (DEBUG == 0)
		return ;
	ft_printf("PRINTING ANTS TAB\n");
	cell = 0;
	while (tab[cell])
	{
		ft_printf("id   : %u\n", tab[cell]->id);
		ft_printf("wait : %u\n", tab[cell]->wait);
		ft_printf("max  : %u\n", tab[cell]->max);
		ft_printf("path : %p\n", tab[cell]->path);
		ft_printf("first: %p\n", tab[cell]->path->rooms->first);
		ft_printf("room : %p\n\n", tab[cell]->current_room);
		cell++;
	}
}

void	print_room(t_room *room)
{
	t_lst	*elem;
	t_room	*child;

	if (DEBUG == 0)
		return ;
	ft_printf("PRINTING ROOM\n");
	ft_printf("room '%s': %p\n", room->name, room);
	ft_printf("\tdist %u\n", room->dist);
	ft_printf("\thas_lvl %u\n", room->has_lvl);
	ft_printf("\twalk %u\n", room->walk);
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
		ft_printf("%s (%u) -- ", child->name, child->dist);
		elem = elem->next;
	}
	ft_printf("\n");
}

void	print_rooms(t_head *rooms)
{
	t_lst	*rooms_lst;

	if (DEBUG == 0)
		return ;
	ft_printf("PRINTING ALL ROOMS\n");
	if (!(rooms_lst = rooms->first))
	{
		ft_printf("no rooms\n");
		return ;
	}
	while (rooms_lst)
	{
		print_room(rooms_lst->content);
		ft_printf("\n");
		rooms_lst = rooms_lst->next;
	}
}

void	print_lvl(t_lvl *lvl)
{
	if (DEBUG == 0)
		return ;
	ft_printf("PRINTING LVL\n");
	ft_printf("lvl %u:\n", lvl->dist);
	print_rooms(lvl->rooms);
}

void	print_anthill(char *anthill)
{
	if (DEBUG == 0)
		return ;
	ft_printf("PRINTING ANTHILL\n");
	ft_printf("anthill:\n---\n'%s'\n---\n", anthill);
}

void	print_path(t_path *path)
{
	t_lst	*path_rooms;
	t_room	*room;

	if (DEBUG == 0)
		return ;
	ft_printf("PRINTING PATH\n");
	path_rooms = path->rooms->first;
	ft_printf("path_address = %p, \n", path);
	ft_printf("path->load = %u, path->room->size = %u\n", path->load, path->rooms->size);
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

void	print_paths_data(t_head *paths)
{
	t_lst		*path_list;
	t_path		*path;

	if (DEBUG == 0)
		return ;
	ft_printf("PRINTING ALL PATHS DATA\n");
	path_list = paths->first;
	while (path_list)
	{
		path = path_list->content;
		ft_printf("addr: %p , load: %u, len: %u - ", path, path->load, path->rooms->size);
		path_list = path_list->next;
	}
	ft_printf("\n");
}

void	print_config(t_config *config)
{
	if (DEBUG == 0)
		return ;
	ft_printf("PRINTING CONFIG\n");
	ft_printf("config turns   : %u\n", config->turns);
	ft_printf("config nb_paths: %u\n", config->paths->size);
	print_paths(config->paths);
	ft_printf("\n");
}

void	print_lem(t_lem *lem, char *args)
{
	if (DEBUG == 0)
		return ;
	ft_printf("PRINTING LEM\n");
	if (!args)
		args = "";
	ft_printf("---\nLEM\n---\n");
	ft_printf("nb_ants   : %zu\n", lem->nb_ants);
	ft_printf("nb_rooms  : %u\n", lem->nb_rooms);
	ft_printf("max_paths : %u\n", lem->max_paths);
	ft_printf("shortest  : %u\n", lem->shortest);
	ft_printf("max_dist  : %u\n", lem->max_dist);
}
