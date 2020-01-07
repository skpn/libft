/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_display_config_lem_lvl.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:14:09 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/03 14:22:35 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

void	print_display(t_display *display)
{
	if (DEBUG == 0)
		return ;
	ft_printf("PRINTING DISPLAY\n");
	ft_printf("last id    : %u\n", display->last_id);
	ft_printf("turn       : %u\n", display->turn);
	ft_printf("lem->turns : %u\n", display->lem_turns);
	ft_printf("total rooms: %u\n", display->total_rooms);
	ft_printf("nb_ants    : %u\n", display->nb_ants);
}

void	print_ants_tab(t_ant **tab)
{
	unsigned	cell;

	if (DEBUG == 0)
		return ;
	ft_printf("PRINTING ANTS TAB\n");
	cell = 0;
	while (tab[cell])
	{
		ft_printf("id   : %u\n", tab[cell]->id);
		ft_printf("wait : %u\n", tab[cell]->wait);
		ft_printf("max  : %u\n", tab[cell]->max);
		ft_printf("path : %p\n", tab[cell]->path);
		ft_printf("first: %p\n", tab[cell]->path->rooms->first);
		ft_printf("room : %p\n\n", tab[cell]->current_room);
		cell++;
	}
}

void	print_rooms(t_head *rooms)
{
	t_room	*room;
	t_lst	*rooms_lst;

	if (DEBUG == 0)
		return ;
	ft_printf("PRINTING ALL ROOMS\n");
	rooms_lst = rooms->first;
	while (rooms_lst)
	{
		room = rooms_lst->content;
		rooms_lst = rooms_lst->next;
		print_room(room);
	}
}

void	print_lvl(t_lvl *lvl)
{
	if (DEBUG == 0)
		return ;
	ft_printf("PRINTING LVL\n");
	ft_printf("lvl %u:\n", lvl->dist);
	print_rooms(lvl->rooms);
}

void	print_config(t_config *config)
{
	if (DEBUG == 0)
		return ;
	ft_printf("PRINTING CONFIG\n");
	ft_printf("config turns   : %u\n", config->turns);
	ft_printf("config nb_paths: %u\n", config->paths->size);
	print_paths(config->paths);
	ft_printf("\n");
}
