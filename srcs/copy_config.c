/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:08:55 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/03 14:09:38 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

t_path	*copy_path(t_path *original_path)
{
	t_path	*new_path;

	if (!(new_path = alloc_new_path()))
		return (NULL);
	new_path->rooms = original_path->rooms;
	new_path->load = original_path->load;
	return (new_path);
}

int		copy_current_paths(t_lem *lem, t_config *new_config)
{
	t_lst		*current_paths_lst;
	t_path		*new_path;
	t_lst		*new_path_lst;

	current_paths_lst = lem->current_config->paths->first;
	while (current_paths_lst)
	{
		if (!(new_path = copy_path(current_paths_lst->content)))
			return (0);
		current_paths_lst = current_paths_lst->next;
		if (!(new_path_lst = ft_lstnew_elem(new_path)))
		{
			free_path(&new_path);
			return (0);
		}
		ft_lstadd(new_config->paths, new_path_lst);
	}
	return (1);
}

void	scramble_end_parents(t_lem *lem)
{
	if (lem->end->parents->size < 2)
		return ;
	if (lem->scramble_flip == 1)
	{
		lem->scramble_flip = 0;
		ft_lstswap_contents(lem->end->parents->last
			, lem->end->parents->last->prev);
	}
	else
	{
		lem->scramble_flip = 1;
		ft_lstswap_contents(lem->end->parents->last, lem->end->parents->first);
	}
}

int		current_to_best(t_lem *lem)
{
	t_config	*new_config;

	if (!(new_config = alloc_new_config(WITH_HEAD)))
		return (0);
	new_config->turns = lem->current_config->turns;
	if (!copy_current_paths(lem, new_config))
	{
		free_config(&new_config);
		return (0);
	}
	if (!lem->best_config
		|| lem->best_config->turns == lem->current_config->turns)
		scramble_end_parents(lem);
	lem->lives = lem->max_lives;
	lem->best_config = new_config;
	return (1);
}
