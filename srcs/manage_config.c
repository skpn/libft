/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 10:27:02 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/07 20:23:48 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static void	pop_dead_paths(t_config *config)
{
	t_lst	*path_lst;
	t_lst	*dead_path_lst;
	t_path	*path;

	path_lst = config->paths->first;
	while (path_lst)
	{
		path = path_lst->content;
		path_lst = path_lst->next;
		if (path->is_dead)
		{
	//		ft_printf(" ---- popping path: ");
	//		print_path(path);
			dead_path_lst = ft_lstpop(config->paths, path);
			if (dead_path_lst)
				ft_lstfree_elem(&dead_path_lst, FREE_LINKS);
		}
	}
}

static int	add_path(t_lem *lem, t_path *new_path)
{
	t_lst		*config_path_lst;
	t_lst		*new_path_lst;
	unsigned	new_path_size;

	lem->lives--;
	new_path_size = new_path->rooms->size;
	if (!(new_path_lst = ft_lstnew_elem(new_path)))
		return (0);
	config_path_lst = lem->current_config->paths->first;
	if (!config_path_lst
		|| ((t_path *)config_path_lst->content)->rooms->size < new_path_size)
		ft_lstadd(lem->current_config->paths, new_path_lst);
	else
	{
		while (config_path_lst->next
			&& ((t_path *)config_path_lst->next->content)->rooms->size
				> new_path_size)
			config_path_lst = config_path_lst->next;
		ft_lstinsert(lem->current_config->paths, config_path_lst, new_path_lst
			, AFTER);
	}
	pop_dead_paths(lem->current_config);
	balance_load(lem);
	return (1);
}

t_lst		*get_room_lst(t_lst *path_lst)
{
	unsigned	highest_walk;
	t_lst		*highest_room;
	t_lst		*first_room_lst;
	t_room		*first_room;

	highest_walk = 0;
	while (path_lst)
	{
		first_room_lst = ((t_path *)path_lst->content)->rooms->first->next;
		first_room = first_room_lst->content;
		if (first_room->walk > highest_walk)
			highest_room = first_room_lst;
		path_lst = path_lst->next;
	}
	return (highest_room);
}

void		reset_path(t_lst *room_lst)
{
	t_room		*room;

	while (room_lst)
	{
		room = room_lst->content;
		room->walk = 0;
		room_lst = room_lst->next;
	}
}

void		reset_highest_path(t_lem *lem)
{
	t_lst		*room_lst;
	t_room		*room;

	room_lst = get_room_lst(lem->best_config->paths->first);
	while (room_lst)
	{
		room = room_lst->content;
		room->walk = 0;
		room_lst = room_lst->next;
	}
}

void		reset_paths(t_lem *lem)
{
	t_lst	*path_lst;

	lem->reset_flip = (lem->reset_flip + 1) % 3;
	path_lst = lem->best_config->paths->first;
	if (lem->reset_flip == 3)
		reset_highest_path(lem);
	else
	{
		if (!lem->reset_flip == 0)
			path_lst = path_lst->next;
		while (path_lst->next)
		{
			reset_path(((t_path *)path_lst->content)->rooms->first);
			path_lst = path_lst->next;
		}
		if (!lem->reset_flip)
		{
			reset_path(((t_path *)path_lst->content)->rooms->first);
		}
	}
}

int			manage_valid_path(t_lem *lem, t_path *path)
{
//	ft_printf("valid path:");
//	print_path(path);
	if (!ft_lstadd_new(lem->paths, path))
		return (0);
	if (!add_path(lem, path))
		return (0);
	if (lem->best_config->turns < lem->current_config->turns)
		return (1);
	if (!update_best_config(lem))
		return (0);
	if (lem->best_config->paths->size > 1 && lem->lives < LIVES_UPPER_LIMIT / 2)
		reset_paths(lem);
	return (1);
}
