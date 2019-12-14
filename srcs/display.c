/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 19:12:41 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/14 20:34:45 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

t_config	*get_best_config(t_head *config_lst)
{
	t_lst		*config_elem;
	t_config	*config;
	t_config	*best;

	config_elem = config_lst->first;
	best = config_elem->content;
	while (config_elem)
	{
		config = config_elem->content;
		config_elem = config_elem->next;
		if (best->turns > config->turns)
			best = config;
	}
	return (best);
}

unsigned	get_total_rooms(t_config *best)
{
	unsigned	total;
	t_lst		*path_elem;
	t_path		*path;

	total = 0;
	path_elem = config->paths->first;
	while (path_elem)
	{
		path = path_elem->content;
		path_elem = path_elem->next;
		total += path->rooms->size;
	}
	return (total);
}

void		clean_anthill(t_lem *lem)
{
	(void)lem;
	return ;
}

void		path_to_tab(t_display *display, t_path *path, unsigned *set_cell)
{
	unsigned	wait;
	unsigned	room_count;

	wait = 0;
	room_count = 0;
	current_room = path->rooms->first;
	while (++room_count <= path->rooms->size)
	{
		display->ants_tab[*set_cell]->id = display->last_id++;
		display->ants_tab[*set_cell]->wait = wait++;
		display->ants_tab[*set_cell]->max = path->turns;
		display->ants_tab[*set_cell]->path = path;
		display->ants_tab[*set_cell]->current_room = path->rooms->first;
		(*set_cell)++;
	}
}

void		set_tab(t_display *display, t_config *best, unsigned total_rooms)
{
	unsigned	set_cell;
	t_lst		*path_elem;

	set_cell = 0;
	path_elem = best->paths->first;
	while (current_cell < total_rooms)
	{
		path_to_tab(display, path_elem->content, &set_cell)
		path_elem = path_elem->next;
	}
}

int			set_display(t_display *display)
{
	unsigned	total_rooms;

	display->best = get_best_config(lem->config_lst);
	total_rooms = get_total_rooms(best);
	if (!(ants_tab = (t_ant *)easymalloc(sizeof(*ants_tab) * total_rooms + 1)))
		return (0);
	set_tab(display, best, total_rooms);
	return (1);
}

void		print_ants_tab(t_display *display)
{
	unsigned	print_cell;
	t_ant		*ant;

	print_cell = 0;
	ant = display->ants_tab[print_cell];
	if (wait <= display->turn)
		printf("L%u-%s", ant->id, ((t_room *)ant->current_room->content)->name);
	ant->current_room = ant->current_room->next;
	while (display->ants_tab[++print_cell])
	{
		if (wait <= display->turn)
			printf("L%u-%s", ant->id, ((t_room *)ant->current_room->content)->name);
		ant->current_room = ant->current_room->next;
		if (!ant->current_room)
		{
			ant->current_room = ant->path->rooms->first;
			ant->id = display->last_id++;
		}
	}
	printf("\n");
}

int			display_lem(t_lem *lem)
{
	t_display	*display;

	if (!(display = alloc_new_display()) || !set_display(display))
		return (0);
	clean_anthill(lem);
	printf("%s\n", lem->anthill);
	while (++display->turn <= lem->turns)
	{
		print_ants_tab(display);
	}
}
