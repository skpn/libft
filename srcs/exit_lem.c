/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_lem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:52:16 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/14 14:04:17 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lem_in.h"

void	free_room(t_head *rooms, t_room **room)
{
	dprintf(g_fd, "freeing room %s\n", (*room)->name);
	print_room(*room);
	ft_lstpop(rooms, *room);
	ft_free((void **)&(*room)->name);
	ft_lstfree(&(*room)->parents, FREE_LINKS, FREE_HEAD);
	ft_lstfree(&(*room)->children, FREE_LINKS, FREE_HEAD);
	ft_free((void **)room);
}

void	free_rooms(t_head **rooms)
{
	t_lst	*elem;
	t_lst	*tmp;

	dprintf(g_fd, "freeing head %p, first: %p, last: %p, size: %u\n"
		, *rooms, (*rooms)->first, (*rooms)->last, (*rooms)->size);
	elem = (*rooms)->first;
	while (elem)
	{
		tmp = elem->next;
		free_room(*rooms, (t_room **)&elem->content);
		ft_lstfree_elem(&elem, FREE_LINKS);
		elem = tmp;
	}
	ft_lstfree_head(rooms);
	printf("rooms freed ok\n");
}

void	free_path(t_path **path)
{
	ft_lstfree(&(*path)->rooms, FREE_LINKS, FREE_HEAD);
	ft_free((void **)path);
}

void	free_paths(t_head **paths)
{
	t_lst	*elem;

	elem = (*paths)->first;
	while (elem)
	{
		free_path((t_path **)&elem->content);
		elem = elem->next;
	}
	ft_lstfree_head(paths);
}

void	free_config(t_config **config)
{
	ft_lstfree(&(*config)->paths, FREE_LINKS, FREE_HEAD);
	ft_free((void **)config);
}

void	free_config_lst(t_head **config_lst)
{
	t_lst	*config_elem;

	config_elem = (*config_lst)->first;
	while (config_elem)
	{
		free_config((t_config **)&(config_elem->content));
		config_elem = config_elem->next;
	}
	ft_lstfree(config_lst, FREE_LINKS, FREE_HEAD);
}

void	free_display(t_display **display)
{
	unsigned	cell;

	cell = 0;
	if ((*display)->ants_tab)
	{
		while (cell < (*display)->total_rooms)
		{
			if ((*display)->ants_tab[cell])
				ft_free((void **)&((*display)->ants_tab[cell]));
		}
		ft_free((void **)&(*display)->ants_tab);
	}
	ft_free((void **)display);
}

int		exit_lem(t_lem **lem, char *msg, int ret)
{
	ft_free((void **)&((*lem)->anthill));
	if ((*lem)->rooms)
	{
		printf("freeing lem rooms, head: %p\n", (*lem)->rooms);
		free_rooms(&(*lem)->rooms);
	}
	if ((*lem)->paths)
	{
		printf("freeing lem paths, head: %p\n", (*lem)->paths);
		free_paths(&((*lem)->paths));
	}
	if ((*lem)->config_lst->first)
	{
		printf("freeing lem config_lst, head: %p\n", (*lem)->config_lst);
		free_config_lst(&((*lem)->config_lst));
	}
	if ((*lem)->current_config)
	{
		printf("freeing lem current_config: %p\n", (*lem)->current_config);
		free_config(&(*lem)->current_config);
	}
	if ((*lem)->display)
	{
		printf("freeing lem display: %p\n", (*lem)->display);
		ft_free((void **)&((*lem)->display));
	}
	msg ? write(1, msg, ft_strlen(msg)) : 0;
	ft_free((void **)lem);
	return (ret);
}
