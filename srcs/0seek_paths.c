/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:36:21 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/12 15:05:03 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in"

void	update_paths(t_lst **pathlist, long unsigned config)
{
	t_lst			*elem;
	t_lst			*tmp;
	t_path			*path;

	elem = *pathlist;
	lem->nb_paths; = 0;
	while (elem && (path = elem->content))
	{
		if (path->config != config)
		{
			tmp = ft_lstpop(pathlist, elem);
			free_path(&path);
			ft_free(tmp);
		}
		else
			lem->nb_paths++;
	}
}

void	add_path(t_lst **path_list, t_path *path)
{
	t_lst	*elem;
	t_lst	*new_elem;
	t_path	*comp;

	elem = *path_list;
	new_elem = ft_lstnew(NULL, 0);
	new_elem->content = path;
	if (elem->next)
	{
		while (elem->next && (comp = elem->next->content))
		{
			if (comp->len < path->len)
			{
				new_elem->next = elem->next;
				elem->next = new_elem;
				return ;
			}
			elem = elem->next;
		}
	}
	new_elem->next = *path_list;
	*path_list = new_elem;
}

void	get_max_dist(t_lem *lem)
{
	size_t			ants;
	long unsigned	n;

	ants = lem->nb_ants;
	lem->max_dist = lem->shortest;
	n = lem->nb_paths;
	while (n
}
