/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 10:27:02 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/14 17:01:31 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

t_config	*copy_config(t_lem *lem)
{
	t_config	*original;
	t_config	*new_config;
	t_head		*new_head;
	
	original = lem->current_config;
	if (!(new_config = alloc_new_config()))
		return (NULL);
	if (!(new_head = ft_lstcpy(original->paths)))
		return (NULL);
	new_config->paths = new_head;
	new_config->turns = original->turns;
	print_config(new_config);
	lem->lives = lem->end->parents->size;
	return (new_config);
}

int		replace_config(t_lem *lem, t_config *old_config)
{
	t_config	*copy;
	t_lst		*old_config_elem;

	if (!(copy = copy_config(lem)))
		return (0);
	old_config_elem = ft_lstfind(lem->config_lst, old_config);
	old_config_elem->content = lem->current_config;
	free_config(&old_config);
	return (1);
}

int		compare_configs(t_lem *lem)
{
	t_lst		*elem;
	t_config	*config;

	elem = lem->config_lst->first;
	while (elem)
	{
		config = (t_config *)elem->content;
		elem = elem->next;
		if (config->paths->size == lem->current_config->paths->size)
		{
			if (lem->current_config->turns < config->turns)
			{
				printf("\nREPLACING CONFIG:\n");
				print_config(config);
				if (!(replace_config(lem, config)))
					return (0);
			}
			return (1);
		}
	}
	PRINTPOSN;
	return (0);
}

int			add_new_config(t_lem *lem, t_config *current_config)
{
	t_config	*copy;

	printf("\nADDING CONFIG\n");
	lem->most_paths++;
	lem->turns = current_config->turns;
	if (!(copy = copy_config(lem)))
		return (0);
	if (!(ft_lstadd_new(lem->config_lst, copy)))
		return (0);
	return (1);
}

void		pop_dead_paths(t_config *config)
{
	t_lst	*path_lst;
	t_path	*path;

	path_lst = config->paths->first;
	while(path_lst)
	{
		path = path_lst->content;
		path_lst = path_lst->next;
		if (path->is_dead)
			ft_lstpop(config->paths, path);
	}
}

// UNTESTED FUNCTION
int			add_path(t_lem *lem, t_config *config, t_path *new_path)
{
	t_lst	*config_path_elem;
	t_lst	*config_path;
	t_lst	*new_path_elem;

	lem->lives--;
	if (!(new_path_elem = ft_lstnew_elem(new_path)))
		return (0);
	printf("\nBEFORE ADDING PATH, CONFIG:\n");
	print_config(config);
	if ((config_path_elem = config->paths->first))
	{
		while (((t_path *)config_path_elem->content)->rooms->size > new_path->rooms->size)
		{
			config_path_elem = config_path_elem->next;
			config_path = config_path_elem->content;
		}
		ft_lstinsert(config->paths, config_path_elem, new_path_elem, BEFORE);
	}
	else
	{
		PRINTPOSN;
		ft_lstadd(config->paths,new_path_elem);
	}
	pop_dead_paths(config);
	balance_load(lem);
	printf("\nUPDATED CONFIG:\n");
	print_config(config);
	return (1);
}

int			manage_valid_path(t_lem *lem, t_path *path)
{
	unsigned	current_nb_paths;
	unsigned	check_alloc;
	t_lst		*new_elem;

	PRINTPOSN;
	if (!ft_lstadd_new(lem->paths, path))
		return (0);
	if (!(new_elem = ft_lstnew_elem(path)))
		return (0);
	if (!add_path(lem, lem->current_config, path))
		return (0);
	current_nb_paths = lem->current_config->paths->size;
	if (current_nb_paths > lem->most_paths
		&& lem->current_config->turns < lem->turns)
		check_alloc = add_new_config(lem, lem->current_config);
	else
		check_alloc = compare_configs(lem);
	return (check_alloc);
}
