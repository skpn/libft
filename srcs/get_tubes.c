/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tubes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 18:00:27 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/06 13:45:09 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static int		add_tubes(t_lem *lem, char *name_1, char *name_2)
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
	if (!ft_lstadd_new(room_1->children, room_2))
		return (MALLOC_ERROR);
	if (!ft_lstadd_new(room_2->children, room_1))
		return (MALLOC_ERROR);
	lem->nb_tubes++;
	return (1);
}

static int		get_tube_names(t_lem *lem, char **name_1, char **name_2)
{
	*name_1 = lem->copy + lem->pos;
	if (!ft_strcmp(*name_1, "\n"))
		return (END);
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

int				get_tubes(t_lem *lem, char *anthill_copy)
{
	int		check_start_end;
	int		ret;
	char	*name_1;
	char	*name_2;

	check_start_end = REJECT_START_END;
	while (anthill_copy[lem->pos] == '#')
		manage_com(lem, anthill_copy, &check_start_end);
	if ((ret = get_tube_names(lem, &name_1, &name_2)) < 1)
		return (ret);
	else if (ret == END)
		return (0);
	if ((ret = add_tubes(lem, name_1, name_2)) < 1)
		return (ret);
	if (!lem->copy[lem->pos])
		return (0);
	return (1);
}
