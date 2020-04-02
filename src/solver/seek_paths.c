/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:36:21 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/02 12:28:21 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

int		reset_room_relaunch(t_h_elem *room_h_elem)
{
	t_room *room;

	room = room_h_elem->content;
	room->walk = 0;
	room->active_path = NULL;
	room->previous_path = NULL;
	return (1);
}

int		clean_after_algo(t_lem *lem)
{
	lem->current_config->turns = 0xFFFFFFFF;
	ft_lstfree(&lem->current_config->paths, FREE_STRUCT, LST_KEEP_HEAD);
	ft_h_iter(lem->table, &reset_room_relaunch);
	if (lem->best_config->turns < lem->final_config->turns)
	{
		if (!(best_to_final(lem)))
			return (0);
	}
	ft_lstfree(&lem->best_config->paths, FREE_STRUCT, LST_KEEP_HEAD);
	lem->best_config->turns = 0xFFFFFFFF;
	return (1);
}

int		set_algo(t_lem *lem)
{
	lem->max_lives = lem->end->parents->size + lem->end->dist * lem->nb_tubes;
	if (lem->max_lives > LIVES_UPPER_LIMIT)
		lem->max_lives = LIVES_UPPER_LIMIT;
	else if (lem->max_lives < LIVES_LOWER_LIMIT)
		lem->max_lives = LIVES_LOWER_LIMIT;
	if (!(lem->current_config = alloc_new_config())
		|| !(lem->best_config = alloc_new_config())
		|| !(lem->final_config = alloc_new_config()))
		return (0);
	if (!(ft_lstadd_new(lem->generic_path->rooms, lem->end)))
		return (0);
	lem->generic_room_lst = lem->generic_path->rooms->last;
	lem->end->active_path = lem->generic_path;
	lem->generic_path_size++;
	return (1);
}

t_path	*copy_generic_path(t_lem *lem)
{
	t_path	*copy_path;
	t_lst	*copy_room_lst;

	if (!(copy_path = alloc_new_path()))
		return (0);
	copy_room_lst = lem->generic_room_lst;
	while (copy_room_lst)
	{
		if (!(ft_lstadd_back_new(copy_path->rooms, copy_room_lst->content)))
			return (0);
		((t_room *)copy_room_lst->content)->active_path = copy_path;
		copy_room_lst = copy_room_lst->next;
	}
	return (copy_path);
}

int		seek_paths(t_lem *lem)
{
	int			check_alloc;

	if (!set_algo(lem))
		return (0);
	while (lem->algo_flip < NB_ALGO_LAUNCHS)
	{
		lem->lives = lem->max_lives;
		lem->reset_flip = 0;
		while (lem->lives)
		{
			lem->lives--;
			if (!(check_alloc = try_path(lem)))
				return (0);
			else if (check_alloc == 1)
			{
				if (!manage_valid_path(lem))
					return (0);
			}
		}
		if (!(clean_after_algo(lem)))
			return (0);
		lem->algo_flip++;
	}
	return (1);
}
