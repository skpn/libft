/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_balancing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 11:00:06 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/14 20:43:48 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

void	balance_load(t_lem *lem)
{
	unsigned	ants;
	unsigned	added_turns;
	unsigned	nb_paths;
	t_lst		*config_path_lst;
	t_path		*current_path;

	config_path_lst = lem->current_config->paths->first;
	nb_paths = lem->current_config->paths->size;
	ants = lem->nb_ants;
	lem->current_config->turns = 0;
	while (config_path_lst && ants)
	{
		current_path = config_path_lst->content;
		config_path_lst = config_path_lst->next;
		added_turns =
			(ants - current_path->rooms->size
			+ ((t_path *)lem->current_config->paths->last->content)->rooms->size)
			/ nb_paths;
		ants -= nb_paths * added_turns;
		lem->current_config->turns += added_turns;
		current_path->load = lem->current_config->turns;
		nb_paths--;
	}
	current_path = lem->current_config->paths->last->content;
	lem->current_config->turns += current_path->rooms->size - 2;
}
