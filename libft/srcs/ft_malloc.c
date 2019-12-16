/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 23:04:53 by sikpenou          #+#    #+#             */
/*   Updated: 2019/11/03 18:53:32 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_head		*get_gc_list(int opt)
{
	static t_head	*gc_list = NULL;

	if (!gc_list && opt == 1)
	{
		if (!(gc_list = (t_head *)malloc(sizeof(*gc_list))))
			return (0);
		gc_list->size = 0;
		gc_list->first = NULL;
		gc_list->last = NULL;
	}
	if (opt == -1)
		gc_list = NULL;
	return (gc_list);
}

int			get_gc_data(int opt)
{
	t_lst	*elem;
	t_head	*gc_list;

	if (!(gc_list = get_gc_list(0)))
		return (0);
	if (opt)
	{
		if (!(elem = gc_list->first))
		{
			ft_printf("gc_list is empty\n");
		}
		else
		{
			ft_printf("\n---\nlist start\n");
			while (elem)
			{
				ft_printf("elem: %p, content: %p, next: %p\n", elem
					, elem->content, elem->next);
				elem = elem->next;
			}
			ft_printf("list end\n---\n\n");
		}
	}
	return (gc_list->size);
}

void		easyfree_gc(void)
{
	t_lst	*elem;
	t_lst	*tmp;
	t_head	*gc_list;

	if (!(gc_list = get_gc_list(0)))
	{
		return ;
	}
	elem = (gc_list)->first;
	while (elem)
	{
		gc_list->size--;
		tmp = elem;
		elem = elem->next;
		if (tmp->content)
		{
			free(tmp->content);
			tmp->content = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
	free(gc_list);
	get_gc_list(-1);
}

void		easyfree(void **match)
{
	t_lst	*elem;
	t_head	*gc_list;

	if (!EASY)
	{
		if (*match)
		{
			free(*match);
			*match = NULL;
		}
		return ;
	}
	if (!*match || !(gc_list = get_gc_list(0)))
		return ;
	if (!(elem = ft_lstpop(gc_list, *match)))
	{
		return ;
	}
	free(*match);
	*match = NULL;
	free(elem);
	elem = NULL;
	gc_list->size--;
}

void		*easymalloc(size_t size)
{
	t_lst	*new_free;
	t_head	*gc_list;
	void	*zone;

	if (!EASY)
	{
		zone = ft_memalloc(size);
		return (zone);
	}
	if (size < 1 || !(gc_list = get_gc_list(1)))
		return (0);
	if (!(new_free = (t_lst *)malloc(sizeof(t_lst))))
		return (0);
	ft_memset(new_free, 0, sizeof(t_lst));
	if ((new_free->content = malloc(size)))
		ft_memset(new_free->content, 0, size);
	new_free->next = NULL;
	ft_lstadd(gc_list, new_free);
	return (new_free->content);
}
