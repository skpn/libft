/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:50:50 by sikpenou          #+#    #+#             */
/*   Updated: 2019/11/03 22:47:20 by sikpenou         ###   ########.fr       */
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

void	print_paths(t_head *paths)
{
	(void)paths;
	printf("paths: paths... paths! haha no paths for you\n");
}

void	print_anthill(char *anthill)
{
	printf("anthill:\n---\n'%s'\n---\n", anthill);
}

void	print_config(t_config *config)
{
	printf("config turns   : %u\n", config->turns);
	printf("config nb_paths: %u\n", config->nb_paths);
	printf("valid paths:\n");
	print_paths(config->valid_paths);
	printf("test paths:\n");
	print_paths(config->test_paths);
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
	printf("turns     : %u\n", lem->turns);
	printf("max_dist  : %u\n", lem->max_dist);
	if (ft_strchr_pos(args, 'a'))
		print_anthill(lem->anthill);
}
