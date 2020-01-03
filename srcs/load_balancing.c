/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_balancing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 11:00:06 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/03 12:08:02 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

void	balance_load(t_lem *lem)
{
	unsigned	ants;
	unsigned	ants_to_all;
	unsigned	nb_paths;
	t_lst		*current_path_elem;
	t_path		*current_path;
	t_path		*longest_path;

	//ft_printf("\nENTERING LOAD BALANCING WITH CONFIG \n");
	//print_config(lem->current_config);
//	ft_printf("current_config addr: %p - best config addr: %p\n"
//		, lem->current_config, lem->best_config);
	nb_paths = lem->current_config->paths->size;
	ants = lem->nb_ants;
	current_path_elem = lem->current_config->paths->first;
	longest_path = current_path_elem->content;
	PRINTPOSN;
	if (lem->best_config)
		print_config(lem->best_config);
	while (current_path_elem)
	{
		current_path = current_path_elem->content;
		PRINTPOSN;
		if (lem->best_config)
			print_paths_data(lem->best_config->paths);
		current_path->load = longest_path->rooms->size - current_path->rooms->size;
		PRINTPOSN;
		if (lem->best_config)
			print_paths_data(lem->best_config->paths);
		ants-= current_path->load;
		current_path_elem = current_path_elem->next;
	}
	ants_to_all = ants / nb_paths;
	ants -= ants_to_all * nb_paths;
	current_path_elem = lem->current_config->paths->first;
	PRINTPOSN;
	if (lem->best_config)
		print_config(lem->best_config);
	while (current_path_elem)
	{
		current_path = current_path_elem->content;
		current_path->load += ants_to_all;
		current_path_elem = current_path_elem->next;
	}
	lem->current_config->turns = longest_path->rooms->size + longest_path->load - 2;
	//ft_printf("Before modulo ants, ants = %u, config = ", ants);
	//print_config(lem->current_config);
	if (ants)
		lem->current_config->turns++;
	current_path_elem = lem->current_config->paths->last;
	while (ants && current_path_elem)
	{
		current_path = current_path_elem->content;
		current_path->load++;
		current_path_elem = current_path_elem->prev;
		ants--;
	}
	if (lem->turns > lem->current_config->turns)
		lem->turns = lem->current_config->turns;
//	ft_printf("\nLEAVING LOAD BALANCING WITH CONFIG \n");
//	print_config(lem->current_config);
}

void	balance_load_v0(t_lem *lem)
{
	unsigned	ants;
	unsigned	added_turns;
	unsigned	nb_paths;
	t_lst		*path_lst;
	t_path		*current_path;

	path_lst = lem->current_config->paths->first;
	nb_paths = lem->current_config->paths->size;
	//printf("Current config size = %u\n", nb_paths);
	ants = lem->nb_ants;
	lem->current_config->turns = 0;
	ft_printf("\nIN LOAD BALANCING WITH CONFIG\n");
	print_config(lem->current_config);
//	printf("line %d, current config turns: %u\n", __LINE__, lem->current_config->turns);
	while (path_lst && ants)
	{
//	printf("line %d, current config turns: %u\n", __LINE__, lem->current_config->turns);
		current_path = path_lst->content;
		path_lst = path_lst->next;
		/*
		printf("(ants - current_path->rooms->size +"
		"((t_path*)lem->current_config->paths->last->content)->rooms->size) "
			"/ nb_paths\n(%u - %u + %u) / %u\n", ants, current_path->rooms->size,
			(((t_path*)lem->current_config->paths->last->content)->rooms->size),
			nb_paths);
		*/
		added_turns =
			(ants - current_path->rooms->size
			+ ((t_path *)lem->current_config->paths->last->content)->rooms->size)
			/ nb_paths;
//i	printf("line %d, added turns: %u, nb_paths %u\n", __LINE__, added_turns,
//	nb_paths);
		ants -= nb_paths * added_turns;
		lem->current_config->turns += added_turns;
		current_path->load = lem->current_config->turns;
		nb_paths--;
	}
	current_path = lem->current_config->paths->last->content;
//	printf("line %d, current config turns: %u\n", __LINE__, lem->current_config->turns);
	lem->current_config->turns += current_path->rooms->size - 2;
	if (lem->turns > lem->current_config->turns)
	{
//		ft_printf("\n\nLATEST BEST CONFIG\n\n");
//		print_config(lem->current_config);
		lem->turns = lem->current_config->turns;
	}
//	printf("\nOUT LOAD BALANCING WITH CURRENT CONFIG TURNS: %u\n",
//	lem->current_config->turns);
	ft_printf("OUT OF BALANCE LOADS, current config = \n");
	print_config(lem->current_config);
}
