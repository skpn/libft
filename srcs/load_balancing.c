/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_balancing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 11:00:06 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/11 18:13:19 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static void	calculate_main_load(t_lem *lem, unsigned *ants
	, t_path *longest_path)
{
	unsigned	ants_to_all;
	unsigned	nb_paths;
	t_lst		*path_lst;
	t_path		*path;

	nb_paths = lem->current_config->paths->size;
	ants_to_all = *ants / nb_paths;
	*ants -= ants_to_all * nb_paths;
	path_lst = lem->current_config->paths->first;
	while (path_lst)
	{
		path = path_lst->content;
		path->load += ants_to_all;
		path_lst = path_lst->next;
	}
	lem->current_config->turns = longest_path->rooms->size
		+ longest_path->load - 2;
	if (*ants)
		lem->current_config->turns++;
}

void		balance_load(t_lem *lem)
{
	unsigned	ants;
	t_lst		*path_lst;
	t_path		*path;
	t_path		*longest_path;

	ants = lem->nb_ants;
	path_lst = lem->current_config->paths->first;
	longest_path = path_lst->content;
	while (path_lst)
	{
		path = path_lst->content;
		path->load = longest_path->rooms->size - path->rooms->size;
		ants -= path->load;
		path_lst = path_lst->next;
	}
	calculate_main_load(lem, &ants, longest_path);
	path_lst = lem->current_config->paths->last;
	while (ants-- && path_lst)
	{
		path = path_lst->content;
		path->load++;
		path_lst = path_lst->prev;
	}
	if (lem->turns > lem->current_config->turns)
		lem->turns = lem->current_config->turns;
}
