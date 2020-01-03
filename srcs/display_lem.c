/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display->c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42->fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 19:12:41 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/03 12:19:15 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

void		start_joined_to_end(t_lem *lem)
{
	unsigned	ant;

	ant = 0;
	ft_printf("L%u-end", ant);
	while (++ant < lem->nb_ants)
	{
		ft_printf(" L%u-end", ant);
	}
	ft_printf("\n");
}

unsigned	get_total_rooms(t_config *best)
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

void		path_to_tab(t_display *display, t_path *path, unsigned *set_cell)
{
	unsigned	wait;
	unsigned	room_count;

	wait = 0;
	room_count = 0;
	while (++room_count < path->rooms->size)
	{
		if (display->last_id < display->nb_ants)
		{
			display->ants_tab[*set_cell]->wait = wait++;
			display->ants_tab[*set_cell]->max = path->load;
			display->ants_tab[*set_cell]->path = path;
			display->ants_tab[*set_cell]->current_room = path->rooms->first->next;
		}
		(*set_cell)++;
	}
}

void		set_tab(t_display *display, unsigned total_rooms)
{
	unsigned	set_cell;
	t_lst		*path_elem;

	set_cell = 0;
	path_elem = display->best->paths->first;
	while (set_cell < total_rooms)
	{
		path_to_tab(display, path_elem->content, &set_cell);
		path_elem = path_elem->next;
	}
}

t_display		*set_display(t_lem *lem)
{
	unsigned	total_rooms;
	t_display	*display;

	total_rooms = get_total_rooms(lem->best_config);
	if (!(display = alloc_new_display(total_rooms)))
		return (NULL);
	//print_display(display);
	display->best = lem->best_config;
	display->nb_ants = lem->nb_ants;
	display->lem_turns = lem->turns;
	set_tab(display, total_rooms);
	return (display);
}

void		print_ant(t_display *display, t_ant *ant)
{
	t_room		*room;

//	printf("first: %u, prefix: '%s'\n", display->first_print, prefix);
	if (ant->wait <= display->turn && ant->current_room)
	{
		if (!ant->id && display->last_id <= display->nb_ants && ant->path->load)
		{
			ant->id = display->last_id++;
			ant->path->load--;
		}
		if (!ant->id)
			return ;
		room = ant->current_room->content;
		if (display->first_print == 1)
		{
			ft_printf("L%u-%s", ant->id, room->name);
			display->first_print = 0;
		}
		else
		{
			ft_printf(" L%u-%s", ant->id, room->name);
		}
		ant->current_room = ant->current_room->next;
		if (!ant->current_room && display->last_id <= display->nb_ants)
		{
			//ft_printf("\nnb_ants = %u, last_id = %u\n", display->nb_ants, display->last_id);
			ant->current_room = ant->path->rooms->first->next;
			ant->id = 0;
		}
	}
}

void		print_ants(t_display *display)
{
	unsigned	print_cell;
	t_ant		*ant;

	print_cell = 0;
	while (display->ants_tab[print_cell])
	{
		ant = display->ants_tab[print_cell];
		print_ant(display, ant);
		print_cell++;
	}
	ft_printf("\n");
}

int			display_lem(t_lem *lem)
{
	t_display	*display;

	if (!(display = set_display(lem)))
		return (0);
	lem->display = display;
	write(1, lem->anthill, ft_strlen(lem->anthill));
	while (display->turn < lem->turns)
	{
		display->first_print = 1;
		print_ants(display);
		display->turn++;
	}
	return (1);
}
