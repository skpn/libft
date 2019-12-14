/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_balancing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 11:00:06 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/14 17:34:21 by sikpenou         ###   ########.fr       */
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

	lem->current_config->turns = lem->shortest;
	config_path_lst = lem->current_config->paths->first;
	nb_paths = lem->current_config->paths->size;
	ants = lem->nb_ants;
	printf("\nBEFORE LOAD BALANCING:\n");
	printf("ants: %u\n", ants);
	printf("shortest: %u\n", lem->shortest);
	printf("nb_paths: %u\n", nb_paths);
	while (config_path_lst)
	{
		current_path = config_path_lst->content;
		config_path_lst = config_path_lst->next;
		added_turns = (ants - current_path->rooms->size + lem->shortest) / nb_paths;
		ants -= nb_paths * added_turns;
		lem->current_config->turns += added_turns;
		current_path->turns = lem->current_config->turns;
		nb_paths--;
	}
}
