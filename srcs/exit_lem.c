/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_lem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:52:16 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/24 15:54:43 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lem_in.h"

void	free_room(t_room **room)
{
	if (!(room))
		return ;
	ft_lstclr(&(*room)->parents);
	ft_lstclr(&(*room)->children);
	ft_free((void **)&(*room)->name);
	free(*room);
	*room = 0;
}

void	free_paths(t_lst **paths)
{
	t_lst	*path;
	t_lst	*tmp;

	if (!(paths))
		return ;
	path = *paths;
	while (path)
	{
		tmp = path->next;
		ft_lstclr(path->content);
		free(path);
		path = 0;
		path = tmp;
	}
	free(*paths);
	*paths = 0;
}

int		exit_lem(t_lem *lem, char *msg, int ret)
{
	if (lem->rooms)
		ft_lstclr(&lem->rooms);
	if (lem->start)
		free_room(&lem->start);
	if (lem->end)
		free_room(&lem->end);
	if (lem->paths)
		free_paths(&lem->paths);
	write(1, msg, ft_strlen(msg));
	return (ret);
}
