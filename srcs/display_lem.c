/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_lem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:36:44 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/07 22:02:19 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "lem_in.h"

void			start_joined_to_end(t_lem *lem)
{
	unsigned	ant;

	write(1, lem->anthill, lem->pos);
	ant = 1;
	ft_printf("L%u-end", ant);
	while (++ant <= lem->nb_ants)
	{
		ft_printf(" L%u-end", ant);
	}
	ft_printf("\n");
}

/*static void		print_ant(t_display *display, t_ant *ant)
{
	t_room		*room;

	if (!(ant->wait <= display->turn && ant->current_room))
		return ;
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
		ft_printf(" L%u-%s", ant->id, room->name);
	ant->current_room = ant->current_room->next;
	if (!ant->current_room && display->last_id <= display->nb_ants)
	{
		ant->current_room = ant->path->rooms->first->next;
		ant->id = 0;
	}
}

static void		print_ants(t_display *display)
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
}*/

void			check_best_config_validity(t_lem *lem, t_config *best_config)
{
	t_lst	*path_lst;
	t_lst	*room_lst;
	t_room	*room;

	path_lst = best_config->paths->first;
	while (path_lst->next)
	{
		room_lst = ((t_path *)path_lst->content)->rooms->first;
		path_lst = path_lst->next;
		while (room_lst)
		{
			room = room_lst->content;
			room_lst = room_lst->next;
			if (room->dist && room != lem->end)
				room->dist = 0;
			else if (room != lem->start && room != lem->end)
			{
				ft_printf("\n\n\nroom %s used %d times :(\n\n\n"
					, room->name, (int)room->dist * -1 + 1);
			}
		}
	}
	ft_printf("\n:)\n\n");
}

int				display_lem(t_lem *lem)
{
	t_display	*display;

	if (!(display = set_display(lem)))
		return (0);
	lem->display = display;
	/*
	write(1, lem->anthill, lem->pos);
	while (display->turn < lem->turns)
	{
		display->first_print = 1;
		print_ants(display);
		display->turn++;
	}
	*/
//	ft_printf("\nmax lives %u, lem turns: %u, nb paths: %u\n\n", lem->max_lives, lem->turns, lem->best_config->paths->size);
//	print_config(lem->best_config);
//	check_best_config_validity(lem, lem->best_config);
	ft_printf("obtained: %u\n", lem->turns);
	return (1);
}
