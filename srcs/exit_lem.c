/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_lem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:52:16 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/31 14:26:52 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lem_in.h"

void	free_path(t_path **path)
{
	ft_lstclr(&(*path)->rooms, 0);
}

void	free_room(t_room **room)
{
	if (!(room))
		return ;
	ft_lstclr(&(*room)->parents, 0);
	ft_lstclr(&(*room)->children, 0);
	ft_free((void **)&(*room)->name);
	ft_free((void **)*room);
	*room = 0;
}

void	free_paths(t_lst **paths)
{
	t_lst	*elem;
	t_path	*path;

	if (!(paths))
		return ;
	elem = *paths;
	while (elem && elem->content)
	{
		path = elem->content;
		free_path(&path);
	}
	ft_free((void **)paths);
}

int		exit_lem(t_lem **lem, char *msg, int ret)
{
	if ((*lem)->paths)
		free_paths(&(*lem)->paths);
	if ((*lem)->rooms)
		ft_lstclr(&(*lem)->rooms, 1);
	msg ? write(1, msg, ft_strlen(msg)) : 0;
	ft_free((void **)&((*lem)->anthill));
	ft_free((void **)lem);
	return (ret);
}
