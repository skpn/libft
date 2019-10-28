/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:50:50 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/24 15:27:46 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

void	print_room(t_room *room)
{
	t_lst	*elem;

	if (!room)
	{
		printf("no room\n");
		return ;
	}
	printf("\tname: %s\n", room->name);
	printf("\tdist: %ld\n", room->dist);
	printf("\tlvl : %ld\n", room->lvl);
	printf("\tparents : ");
	fflush(0);
	elem = room->parents;
	while (elem && elem->content)
	{
		printf("%s ", ((t_room *)(elem->content))->name);
		elem = elem->next;
	}
	printf("\n\tchildren: ");
	elem = room->children;
	while (elem)
	{
		printf("%s ", ((t_room *)(elem->content))->name);
		elem = elem->next;
	}
	printf("\n");
}

void	print_anthill(t_lem *lem)
{
	write(1, lem->anthill, ft_strlen(lem->anthill));
}

void	print_rooms(t_lst *rooms)
{
	t_lst	*elem;

	elem = rooms;
	printf("rooms : \n");
	while (elem)
	{
		print_room(elem->content);
		elem = elem->next;
	}
}

void	print_paths(t_lst *paths)
{
	(void)paths;
	printf("paths: paths... paths! haha no paths for you\n");
}

void	print_lem(t_lem *lem, char *args)
{
	if (!args)
		args = "";
	printf("nb ants  : %lu\n", lem->nb_ants);
	printf("nb rooms : %lu\n", lem->nb_rooms);
	if (ft_strchr_pos(args, 'a') > -1)
		printf("anthill  :\n---\n%s\n---\n", lem->anthill);
	if (ft_strchr_pos(args, 'r') > -1)
		print_rooms(lem->rooms);
	if (ft_strchr_pos(args, 's') > -1)
	{
		printf("start    :\n");
		print_room(lem->start);
	}
	if (ft_strchr_pos(args, 'e') > -1)
	{
		printf("end      :\n");
		print_room(lem->end);
	}
	if (ft_strchr_pos(args, 'p') > -1)
		print_paths(lem->paths);
}
