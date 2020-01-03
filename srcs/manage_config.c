/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 10:27:02 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/03 12:53:30 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

t_path	*copy_path(t_path *original_path)
{
	t_path	*new_path;

	if (!(new_path = alloc_new_path()))
		return (NULL);
	new_path->rooms = original_path->rooms;
	new_path->load = original_path->load;
	return (new_path);
}

void	scramble_end_parents(t_lem *lem)
{
	if (lem->end->parents->size < 2)
		return ;
	if (lem->scramble_flip == 1)
	{
		lem->scramble_flip = 0;
		ft_lstswap_contents(lem->end->parents->last, lem->end->parents->last->prev);
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
	t_head		*new_head;
	t_lst		*current_paths_lst;
	t_lst		*new_path_lst;
	t_path		*new_path;
	
	if (!(new_config = alloc_new_config(WITHOUT_HEAD)))
		return (0);
	if (!(new_head = ft_lstnew_head(NULL, NULL)))
		return (0);
	new_config->paths = new_head;
	new_config->turns = lem->current_config->turns;
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
		ft_lstadd(new_head, new_path_lst);
	}
	if (!lem->best_config || lem->best_config->turns == lem->current_config->turns)
		scramble_end_parents(lem);
	lem->lives = lem->max_lives;
	lem->best_config = new_config;
	return (1);
}

void	pop_dead_paths(t_config *config)
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
			dead_path_lst = ft_lstpop(config->paths, path);
			if (dead_path_lst)
				ft_lstfree_elem(&dead_path_lst, FREE_LINKS);
		}
	}
}

int		add_path(t_lem *lem, t_path *new_path)
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
			&& ((t_path *)config_path_lst->next->content)->rooms->size > new_path_size)
			config_path_lst = config_path_lst->next;
		ft_lstinsert(lem->current_config->paths, config_path_lst, new_path_lst, AFTER);
	}
	pop_dead_paths(lem->current_config);
	balance_load(lem);
	return (1);
}

int		manage_valid_path(t_lem *lem, t_path *path)
{
	if (!ft_lstadd_new(lem->paths, path))
		return (0);
	if (!add_path(lem, path))
		return (0);
	if (lem->best_config && lem->best_config->turns > lem->current_config->turns)
		free_config(&lem->best_config);
	if (!lem->best_config && !current_to_best(lem))
		return (0);
	return (1);
}
