/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:50:50 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/31 14:14:18 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

#define PARENTS 1
#define CHILDREN 2
#define FAMILY 3

void	print_basic(t_room *room, char *args, int opt)
{
	char	*sep;

	sep = opt == 1 ? "\n\t" : "";
	sep = opt == 2 ? "\n" : sep;
	ft_strchr_pos(args, 'n') > -1 ? printf("%sname: %s ", sep, room->name) : 0;
	ft_strchr_pos(args, 'p') > -1 ? printf("%saddr %p ", sep, room) : 0;
	ft_strchr_pos(args, 'd') > -1 ? printf("%sdist: %ld ", sep, room->dist) : 0;
	ft_strchr_pos(args, 'w') > -1 ? printf("%swalk: %ld ", sep, room->walk) : 0;
	opt ? printf("\n") : 0;
}

void	print_family(t_room *o_room, int opt, char *args)
{
	t_lst	*elem;
	t_room	*room;

	if (!o_room)
	{
		printf("no room\n");
		return ;
	}
	printf("%s: ", opt == PARENTS || opt == FAMILY ? "parents" : "children: ");
	elem = opt == PARENTS || opt == FAMILY ? o_room->parents : o_room->children;
	while (elem && elem->content)
	{
		room = elem->content;
		print_basic(room, args, 0);
		printf("-- ");
		elem = elem->next;
	}
	printf("\n");
	opt == FAMILY ? print_family(o_room, CHILDREN, args) : 0;
}

void	print_room(t_room *room, char *args, int opt)
{

	if (!room)
	{
		printf("no room\n");
		return ;
	}
	print_basic(room, args, opt);
	ft_strchr_pos(args, 'p') > -1 ? print_family(room, PARENTS, "n") : 0;
	ft_strchr_pos(args, 'c') > -1 ? print_family(room, CHILDREN, "n") : 0;
	ft_strchr_pos(args, 'f') > -1 ? print_family(room, FAMILY, "n") : 0;
}

void	print_rooms(t_lst *rooms, char *args, int opt)
{
	t_lst	*elem;

	elem = rooms;
	printf("rooms : \n");
	while (elem)
	{
		print_room(elem->content, args, opt);
		elem = elem->next;
	}
}

void	print_paths(t_lst *paths)
{
	(void)paths;
	printf("paths: paths... paths! haha no paths for you\n");
}

void	print_anthill(t_lem *lem)
{
	write(1, lem->anthill, ft_strlen(lem->anthill));
}

void	print_lem(t_lem *lem, char *args)
{
	if (!args)
		args = "";
	printf("---\nLEM\n---\n");
	printf("nb ants  : %lu\n", lem->nb_ants);
	printf("nb rooms : %lu\n", lem->nb_rooms);
	printf("nb max p : %lu\n", lem->max_paths);
	if (ft_strchr_pos(args, 'a') > -1)
		printf("anthill  :\n---\n%s\n---\n", lem->anthill);
	if (ft_strchr_pos(args, 'r') > -1)
		print_rooms(lem->rooms, "fnd", 2);
	if (ft_strchr_pos(args, 's') > -1)
	{
		printf("start    :\n");
		print_room(lem->start, "fndp", 2);
	}
	if (ft_strchr_pos(args, 'e') > -1)
	{
		printf("end      :\n");
		print_room(lem->end, "fndp", 2);
	}
	if (ft_strchr_pos(args, 'p') > -1)
		print_paths(lem->paths);
}
