/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_lem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:36:44 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/06 16:50:15 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "lem_in.h"

void			start_joined_to_end(t_lem *lem)
{
	unsigned	ant;

	write(1, lem->anthill, ft_strlen(lem->anthill));
	ant = 1;
	ft_printf("L%u-end", ant);
	while (++ant <= lem->nb_ants)
	{
		ft_printf(" L%u-end", ant);
	}
	ft_printf("\n");
}


static void		print_ant(t_display *display, t_ant *ant)
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
}


void			nb_walked_rooms_per_lvl(t_lem *lem)
{
	unsigned	index;
	t_lst		*index_lst;
	t_h_elem	*h_elem;
	t_room		*room;
	unsigned	lvl_not_walked;
	unsigned	lvl_rooms;
	unsigned	lvl;

	index = 0;
	lvl = 131;
	while (lvl >= 0 && lvl < 10000000)
	{
		lvl_not_walked = 0;
		lvl_rooms = 0;
		index = 0;
		while (index < lem->table->size)
		{
			if (lem->table->array[index].first)
			{
				index_lst = lem->table->array[index].first;
				while (index_lst)
				{
					h_elem = index_lst->content;
					index_lst = index_lst->next;
					room = h_elem->content;
					if (room->dist == lvl)
						lvl_rooms++;
					if (!room->walk && room->dist == lvl)
						lvl_not_walked++;
				}
			}
			index++;
		}
		ft_printf("lvl %u: at walk = 0 : %u / %u\n"
			, lvl, lvl_not_walked, lvl_rooms);
		lvl--;
	}
}


int				display_lem(t_lem *lem)
{
	t_display	*display;

	if (!(display = set_display(lem)))
		return (0);
	lem->display = display;
	
	//write(1, lem->anthill, ft_strlen(lem->anthill));
	while (display->turn < lem->turns)
	{
		display->first_print = 1;
		print_ants(display);
		display->turn++;
	}
	
	print_room(lem->start);
	ft_printf("start children: %u\n", lem->start->children->size);
	print_room(lem->end);
	ft_printf("end parents: %u\n", lem->end->parents->size);
	ft_printf("scrambled: %u\n", lem->scramble_ctr);
	nb_walked_rooms_per_lvl(lem);
	ft_printf("nb_paths = %u\n", lem->best_config->paths->size);
	ft_printf("turns: %u\n", lem->turns);
	return (1);
}
