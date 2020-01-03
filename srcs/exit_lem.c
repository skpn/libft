/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_lem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:52:16 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/03 14:02:08 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lem_in.h"

void	free_lvl(t_lvl **lvl)
{
	ft_lstfree(&(*lvl)->rooms, FREE_LINKS, FREE_HEAD);
	easyfree((void **)lvl);
}

void	free_table_room(void **void_room)
{
	t_room	**room;

	room = (t_room **)void_room;
	ft_lstfree(&(*room)->parents, FREE_LINKS, FREE_HEAD);
	ft_lstfree(&(*room)->children, FREE_LINKS, FREE_HEAD);
	easyfree((void **)room);
}

void	free_config(t_config **config)
{
	ft_lstfree(&(*config)->paths, FREE_LINKS, FREE_HEAD);
	easyfree((void **)config);
}

void	free_display(t_display **display)
{
	unsigned	cell;

	cell = 0;
	if ((*display)->ants_tab)
	{
		while (cell < (*display)->total_rooms)
		{
			if ((*display)->ants_tab[cell])
			{
				easyfree((void **)&((*display)->ants_tab[cell]));
			}
			cell++;
		}
		easyfree((void **)&(*display)->ants_tab);
	}
	easyfree((void **)display);
}

int		exit_lem(t_lem **lem, char *msg, int ret)
{
	if ((*lem)->table)
		ft_hash_free_table((*lem)->table, FREE_BOTH);
	if ((*lem)->anthill)
		easyfree((void **)&(*lem)->anthill);
	if ((*lem)->copy)
		easyfree((void **)&(*lem)->copy);
	if ((*lem)->paths)
		free_paths(&((*lem)->paths));
	if ((*lem)->best_config)
		free_config(&((*lem)->best_config));
	if ((*lem)->current_config)
		free_config(&(*lem)->current_config);
	if ((*lem)->display)
		free_display(&(*lem)->display);
	msg ? ft_putstr(msg) : 0;
	easyfree((void **)lem);
	return (ret);
}
