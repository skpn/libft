/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_lem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:52:16 by sikpenou          #+#    #+#             */
/*   Updated: 2019/11/05 23:44:43 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lem_in.h"

void	free_room(t_head *rooms, t_room **room)
{
	t_lst	*elem;

	printf("freeing room:\n");
	print_room(*room);
	elem = ft_lstpop(rooms, *room);
	ft_lstfree_elem(&elem, FREE_LINKS);
	g_addr = *room;
	printf("line %d, *room: %p, *room name: %p\n", __LINE__, *room, (*room)->name);
	ft_free((void **)&(*room)->name);
	printf("line %d, *room: %p\n", __LINE__, *room);
	PRINTPOSN;
	ft_lstprint((*room)->parents, "parents", 0);
	ft_lstfree_head(&(*room)->parents);
	PRINTPOSN;
	ft_lstprint((*room)->children, "children", 0);
	ft_lstfree_head(&(*room)->children);
	PRINTPOSN;
	ft_free((void **)room);
	printf("freed ok\n");
}

void	free_rooms(t_head **rooms)
{
	t_lst	*elem;

	printf("freeing head %p, first: %p, last: %p, size: %u\n"
		, *rooms, (*rooms)->first, (*rooms)->last, (*rooms)->size);
	elem = (*rooms)->first;
	while (elem)
	{
		printf("elem: %p, elem content: %p\n", elem, elem->content);
		free_room(*rooms, (t_room **)&elem->content);
		elem = elem->next;
		ft_free((void **)&elem->prev);
	}
	printf("rooms freed\n");
	ft_lstfree_head(rooms);
	printf("freed ok\n");
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
	ft_lstfree(&(*config)->valid_paths, FREE_LINKS, FREE_HEAD);
	ft_lstfree(&(*config)->test_paths, FREE_LINKS, FREE_HEAD);
	ft_free((void **)config);
}

int		exit_lem(t_lem *lem, char *msg, int ret)
{
	if (lem->config)
		free_config(&lem->config);
	if (lem->rooms)
	{
		PRINTPOSN;
		print_rooms(lem->rooms);
		free_rooms(&lem->rooms);
	}
	msg ? write(1, msg, ft_strlen(msg)) : 0;
	ft_free((void **)&lem->anthill);
	ft_free((void **)&lem);
	return (ret);
}
