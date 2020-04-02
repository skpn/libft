/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:34:41 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/13 15:45:22 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static unsigned	get_total_rooms(t_config *best)
{
	unsigned	total;
	t_lst		*path_elem;
	t_path		*path;

	total = 0;
	path_elem = best->paths->first;
	while (path_elem)
	{
		path = path_elem->content;
		path_elem = path_elem->next;
		total += path->rooms->size - 1;
	}
	return (total);
}

static void		path_to_tab(t_display *display, t_path *path, unsigned *cell)
{
	unsigned	wait;
	unsigned	room_count;

	wait = 0;
	room_count = 0;
	while (++room_count < path->rooms->size)
	{
		if (display->last_id <= display->nb_ants)
		{
			display->ants_tab[*cell]->wait = wait++;
			display->ants_tab[*cell]->path = path;
			display->ants_tab[*cell]->current_room = path->rooms->first->next;
		}
		(*cell)++;
	}
}

static void		set_tab(t_display *display, unsigned total_rooms)
{
	unsigned	cell;
	t_lst		*path_elem;

	cell = 0;
	path_elem = display->best->paths->first;
	while (cell < total_rooms)
	{
		path_to_tab(display, path_elem->content, &cell);
		path_elem = path_elem->next;
	}
}

t_display		*set_display(t_lem *lem)
{
	unsigned	total_rooms;
	t_display	*display;

	total_rooms = get_total_rooms(lem->final_config);
	if (!(display = alloc_new_display(total_rooms)))
		return (NULL);
	display->best = lem->final_config;
	display->nb_ants = lem->nb_ants;
	display->lem_turns = lem->turns;
	set_tab(display, total_rooms);
	return (display);
}
