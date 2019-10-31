/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:18:45 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/31 14:49:42 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

#define BAD_GRAPH 0
#define OK 1
t_lst	*get_next_lvl(t_lst *current_lvl)
{
	t_lst	*elem;
	t_room	*room;
	t_lst	*next_lvl;

	if (!(next_lvl = ft_lstnew(NULL, 0)))
		return (0);
	elem = current_lvl;
	while (elem && (room = elem_content))
	{
		ft_lstjoin(room->children, next_lvl);
		elem = elem->next;
	}
	return (next_lvl);
}

void	set_parents(t_lst *current_lvl, long dist)
{
	t_lst	*elem;
	t_room	*parent;
	t_lst	*child_elem;
	t_room	*child;
	t_lst	*transfer;

	elem = current_lvl;
	while (elem && (parent = elem->content))
	{
		child_elem = parent->children;
		while (child_elem && child_elem->content)
		{
			child = child_elem->content;
			if (child_dist <= dist)
			{
				transfer = ft_lstpop(parent->children, child_elem);
				ft_lstadd(parent->parents, transfer);
			}
			child_elem = child_elem->next;
		}
		elem = elem->next;
	}
}

long	set_next_lvl_dist(t_lem *lem, t_lst *next_lvl, long dist)
{
	t_lst	*elem;
	t_room	*room;
	long	ctr;

	elem = next_lvl;
	ctr = 0;
	while (elem && (room = elem->content))
	{
		if (room->dist > dist)
			room->dist = dist;
		if (!(ft_strcmp(room->name, "end")) && lem->nb_paths == 0)
		{
			lem->shortest = dist;
			lem->longest = dist;
			lem->nb_paths = 1;
			get_max_len(lem);
		}
		elem = elem->next;
		++ctr;
	}
	return (ctr);
}

int		set_lvl_n(t_lem *lem, t_lst *current_lvl, t_lst *next_lvl)
{
	long	dist;
	long	ctr;

	dist = 1;
	while (dist < lem->max_len)
	{
		if (!(next_lvl = get_next_lvl(current_lvl)))
			return (0);
		if (!(next_lvl->content) && lem->nb_paths == 0)
			return (0);
		if ((ctr = set_next_lvl_dist(lem, next_lvl, dist))
			&& ctr < lem->max_paths)
			lem->max_paths = ctr;
		else if (!ctr && lem->nb_paths == 0)
			return (0);
		set_parents(current_lvl);
		ft_lstclr(current_lvl, 0);
		current_lvl = next_lvl;
	}
	return (1);
}

int		set_graph(t_lem *lem)
{
	t_lst	*current_lvl;
	t_lst	*next_lvl;

	if (!(current_lvl = ft_lstnew(NULL, 0)))
		return (0);
	start->dist = 0;
	current_lvl->content = start;
	if (!(set_lvl_n(lem, current_lvl, NULL, 1)))
		return (BAD_GRAPH);
	return (OK);
}
