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

t_room	*seek_second_room(t_lst *elem, char *name)
{
	t_room	*room;

	while (elem)
	{
		room = (t_room *)elem->content;	
		if (!ft_strcmp(room->name, name))
			return (room);
		elem = elem->next;
	}
	return (NULL);
}

int		add_links(t_lem *lem, char *name_1, char *name_2)
{
	t_room	*room_1;
	t_room	*room_2;

	if (!(room_1 = ft_hash_get_content(lem->table, name_1)))
		return (PARSING_ERROR);
	if (!(room_2 = ft_hash_get_content(lem->table, name_2)))
		return (PARSING_ERROR);
	if (room_1 == room_2)
		return (PARSING_ERROR);
	if (ft_lstfind(room_1->children, room_2))
		return (1);
//	printf("adding:\n");
//	print_room(room_1);
//	print_room(room_2);
	if (!ft_lstadd_new(room_1->children, room_2))
		return (MALLOC_ERROR);
	if (!ft_lstadd_new(room_2->children, room_1))
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

	check_start_end = REJECT_START_END;
	if (anthill_copy[lem->pos] == '#')
		manage_com(lem, anthill_copy, &check_start_end);
	if ((ret = get_link_names(lem, &name_1, &name_2)) < 1)
		return (ret);
	if ((ret = add_links(lem, name_1, name_2)) < 1)
	{
		return (ret);
	}
//	printf("%s %d, added link: %s-%s\n", __func__, __LINE__,name_1, name_2);
	if (!lem->copy[lem->pos])
		return (0);
	return (1);
}
