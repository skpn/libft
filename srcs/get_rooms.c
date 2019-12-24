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

int		skip_coord(t_lem *lem)
{
	if (lem->copy[lem->pos++] != '\0')
		return (PARSING_ERROR);
	while (lem->copy[lem->pos] <= '9' && lem->copy[lem->pos] >= '0')
	{
//		printf("%s %d, cpy[lem->pos]: '%c'\n", __func__, __LINE__, lem->copy[lem->pos]);
		lem->pos++;
	}
	if (lem->copy[lem->pos++] != ' ')
		return (PARSING_ERROR);
	while (lem->copy[lem->pos] <= '9' && lem->copy[lem->pos] >= '0')
	{
//		printf("%s %d, cpy[lem->pos]: '%c'\n", __func__, __LINE__, lem->copy[lem->pos]);
		lem->pos++;
	}
//	printf("%s %d, cpy[lem->pos]: '%c', lem->pos = %u\n", __func__, __LINE__, lem->copy[lem->pos], lem->pos);
	if (lem->copy[lem->pos++] != '\n')
		return (PARSING_ERROR);
//	printf("%s %d, cpy[lem->pos]: '%c', lem->pos = %u\n", __func__, __LINE__, lem->copy[lem->pos], lem->pos);
	return (1);
}

int		check_same_name(t_lem *lem, char *name_to_check)
{
	t_lst	*room_elem;
	t_room	*room;

	//printf("IN CHECK_SAME NAME\n");
	room_elem = lem->rooms->first;
	while (room_elem)
	{
		room = room_elem->content;
		if (!ft_strcmp(room->name, name_to_check))
		{
			//printf("SAME NAME FOUND\n");
			return (PARSING_ERROR);
		}
		room_elem = room_elem->next;
	}
	//printf("same name not found\n");
	return (1);
}

int		get_name(t_lem *lem, char **name)
{
	unsigned	start_pos;
	char		c;

//	printf("getting name from:\n'%s'", lem->copy + lem->pos);
	if ((c = lem->copy[lem->pos]) == 'L' || c == '-' || c == '\0' || c == ' ')
		return (PARSING_ERROR);
	start_pos = lem->pos;
	while ((c = lem->copy[++lem->pos]) != ' ')
	{
	//	printf("%c\n", c);
		if (c == '\0' || c == '\n')
		{
			lem->pos = start_pos;
			return (PARSING_ERROR);
		}
		else if (c == '-')
		{
			lem->pos = start_pos;
			return (0);
		}
	}
	*name = lem->copy + start_pos;
	lem->copy[lem->pos] = 0;
//	PRINTPOSN;
	return (skip_coord(lem));
}

int		get_rooms(t_lem *lem, char *anthill_copy)
{
	int		check_start_end;
	int		ret;
	t_room	*room;
	char	*name;

//	printf("lem pos: %u\n", lem->pos);
	check_start_end = ACCEPT_START_END;
	if (anthill_copy[lem->pos] == '#')
		if (manage_com(lem, anthill_copy, &check_start_end) == PARSING_ERROR)
			return (PARSING_ERROR);
	if ((ret = get_name(lem, &name)) < 1)
	{
		return (ret);
	}
	if (check_same_name(lem, name) <= 0)
		return (PARSING_ERROR);
	if (!(room = alloc_new_room()))
		return (MALLOC_ERROR);
	if (!ft_lstadd_new(lem->rooms, room))
		return (MALLOC_ERROR);
	room->name = name;
	if (check_start_end == START)
		lem->start = room;
	else if (check_start_end == END)
		lem->end = room;
//	printf("alloc'ed room:\n");
//	print_room(room);
	return (1);
}
