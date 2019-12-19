/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:41:30 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/19 19:01:07 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

int		skip_coord(t_lem *lem, char *anthill_copy)
{
	while (anthill_copy[lem->pos] <= '9' && anthill_copy[lem->pos] >= '0')
	{
//		printf("%s %d, cpy[lem->pos]: '%c'\n", __func__, __LINE__, anthill_copy[lem->pos]);
		lem->pos++;
	}
	if (anthill_copy[lem->pos++] != ' ')
		return (PARSING_ERROR);
	while (anthill_copy[lem->pos] <= '9' && anthill_copy[lem->pos] >= '0')
	{
//		printf("%s %d, cpy[lem->pos]: '%c'\n", __func__, __LINE__, anthill_copy[lem->pos]);
		lem->pos++;
	}
//	printf("%s %d, cpy[lem->pos]: '%c'\n", __func__, __LINE__, anthill_copy[lem->pos]);
	if (anthill_copy[lem->pos++] != '\n')
		return (PARSING_ERROR);
//	printf("%s %d, cpy[lem->pos]: '%c', lem->pos = %u\n", __func__, __LINE__, anthill_copy[lem->pos], lem->pos);
	return (1);
}

int		get_name(t_lem *lem, t_room *room, char *anthill_copy)
{
	unsigned	start_pos;

	start_pos = lem->pos;
	if (anthill_copy[lem->pos] == 'L')
		return (PARSING_ERROR);
	room->name = anthill_copy + lem->pos;
	while(anthill_copy[lem->pos] && anthill_copy[lem->pos] != '\n')
	{
//		printf("%s %d, cpy[lem->pos]: '%c', lem->pos = %u\n", __func__, __LINE__, anthill_copy[lem->pos], lem->pos);
		if (anthill_copy[lem->pos] == ' ')
		{
			anthill_copy[lem->pos++] = '\0';
			return (skip_coord(lem, anthill_copy));
		}
		else if (anthill_copy[lem->pos] == '-')
		{
//			printf("%s %d, start pso: %u\n", __func__, __LINE__, start_pos);
			free_room(lem->rooms, &room);
			lem->pos = start_pos;
			return (0);
		}
		lem->pos++;
	}
	return (PARSING_ERROR);
}

int		check_same_name(t_lem *lem, t_room *room_to_check)
{
	t_lst	*room_elem;
	t_room	*room;

	if (!lem->rooms->first)
		return (1);	
	room_elem = lem->rooms->first->next;
	while (room_elem)
	{
		room = room_elem->content;
		if (!ft_strcmp(room->name, room_to_check->name))
			return (PARSING_ERROR);
		room_elem = room_elem->next;
	}
	return (1);
}

int		get_rooms(t_lem *lem, char *anthill_copy)
{
	int		check_start_end;
	int		ret;
	t_room	*room;

//	printf("lem pos: %u\n", lem->pos);
	check_start_end = ACCEPT_START_END;
	if (anthill_copy[lem->pos] == '#')
		manage_com(lem, anthill_copy, &check_start_end);
	if (!(room = alloc_new_room()))
		return (MALLOC_ERROR);
	if (!ft_lstadd_new(lem->rooms, room))
		return (MALLOC_ERROR);
	if ((ret = get_name(lem, room, anthill_copy)) < 1)
	{
//		printf("%s, ret: %d\n", __func__, ret);
		return (ret);
	}
//	printf("%s %d, ret: %d\n", 
	if (!(check_same_name(lem, room)))
		return (PARSING_ERROR);
	if (check_start_end == START)
		lem->start = room;
	else if (check_start_end == END)
		lem->end = room;
	return (1);
}
