/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:41:30 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/07 11:10:34 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static int		skip_coord(t_lem *lem)
{
	if (lem->copy[lem->pos++] != '\0')
		return (PARSING_ERROR);
	while (lem->copy[lem->pos] <= '9' && lem->copy[lem->pos] >= '0')
	{
		lem->pos++;
	}
	if (lem->copy[lem->pos++] != ' ')
		return (PARSING_ERROR);
	while (lem->copy[lem->pos] <= '9' && lem->copy[lem->pos] >= '0')
	{
		lem->pos++;
	}
	if (lem->copy[lem->pos++] != '\n')
		return (PARSING_ERROR);
	return (1);
}

static int		check_same_name(t_lem *lem, char *name_to_check)
{
	if (ft_hash_get_elem(lem->table, name_to_check))
		return (PARSING_ERROR);
	return (1);
}

static int		get_name(t_lem *lem, char **name)
{
	unsigned	start_pos;
	char		c;

	if ((c = lem->copy[lem->pos]) == 'L' || c == '-' || c == '\0' || c == ' ')
		return (PARSING_ERROR);
	start_pos = lem->pos;
	while ((c = lem->copy[++lem->pos]) != ' ')
	{
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
	return (skip_coord(lem));
}

int				get_rooms(t_lem *lem, char *anthill_copy)
{
	int		check_start_end;
	int		ret;
	t_room	*room;
	char	*name;

	check_start_end = ACCEPT_START_END;
	while (anthill_copy[lem->pos] == '#')
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
	room->name = name;
	ft_hash_add_elem(lem->table, room->name, room);
	if (check_start_end == START)
		lem->start = room;
	else if (check_start_end == END)
		lem->end = room;
	return (1);
}
