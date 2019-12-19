/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tubes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 18:00:27 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/19 19:03:13 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

int		add_links(t_lem *lem, char *name1, char *name2)
{
	t_lst	*elem;
	t_room	*room;
	t_room	*room1;
	t_room	*room2;
	int		ctr;

//	printf("name 1: %s, name 2: %s\n", name1, name2);
	elem = lem->rooms->first;
	ctr = 0;
	while (elem && ctr < 2)
	{
		room = (t_room *)elem->content;	
		if (!ft_strcmp(room->name, name1) && ++ctr)
			room1 = room;
		else if (!ft_strcmp(room->name, name2) && ++ctr)
			room2 = room;
		elem = elem->next;
	}
	if (ctr != 2 || room1 == room2)
		return (PARSING_ERROR);
	if (ft_lstfind(room1->children, room2))
		return (1);
//	printf("adding:\n");
//	print_room(room1);
//	print_room(room2);
	if (!ft_lstadd_new(room1->children, room2))
		return (MALLOC_ERROR);
	if (!ft_lstadd_new(room2->children, room1))
		return (MALLOC_ERROR);
	return (1);
}

int		get_link_names(t_lem *lem, char **name_1, char **name_2)
{
	*name_1 = lem->copy + lem->pos;
	while (lem->copy[lem->pos] && lem->copy[lem->pos] != '-')
		lem->pos++;
	if (lem->copy[lem->pos] != '-')
		return (PARSING_ERROR);
	lem->copy[lem->pos++] = 0;
	*name_2 = lem->copy + lem->pos;
	while (lem->copy[lem->pos] && lem->copy[lem->pos] != '\n')
		lem->pos++;
	if (lem->copy[lem->pos] != '\n')
		return (PARSING_ERROR);
	lem->copy[lem->pos++] = 0;
	return (1);
}

int		get_tubes(t_lem *lem, char *anthill_copy)
{
	int		check_start_end;
	int		ret;
	char	*name_1;
	char	*name_2;

//	printf("lem pos: %u\n", lem->pos);
	check_start_end = REJECT_START_END;
	if (anthill_copy[lem->pos] == '#')
		manage_com(lem, anthill_copy, &check_start_end);
	if ((ret = get_link_names(lem, &name_1, &name_2)) < 1)
		return (ret);
	if ((ret = add_links(lem, name_1, name_2)) < 1)
	{
		PRINTPOSN;
//		printf("%s, ret: %d\n", __func__, ret);
		return (ret);
	}
//	printf("%s %d, ret: %d\n", 
	if (!lem->copy[lem->pos])
		return (0);
	return (1);
}
