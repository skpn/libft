/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lem_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:01:15 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/02 12:26:09 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem_in.h"

void	free_path(t_path **path)
{
	ft_lstfree(&(*path)->rooms, FREE_STRUCT, LST_FREE_HEAD);
	easyfree((void **)path);
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
	ft_lstfree(paths, FREE_STRUCT, LST_FREE_HEAD);
}
