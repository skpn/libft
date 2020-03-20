/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easymalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 23:04:53 by sikpenou          #+#    #+#             */
/*   Updated: 2020/03/19 18:39:14 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** this is a small garbage collector (gc) ; it does keep track of unused
** pointers
** set EASY to 0 in libft.h to turn it off
** each program should have its
** separate gc branch
** to start a separate gc branch, call get_gc with the NEW option
** at the end of a program, free the program's gc branch with  free_gc and the
** 	CURRENT option (option ALL frees all branches, including those of the
** 	calling program if it uses easymalloc too)
*/

/*
** this function takes a t_lst pointer and points it to the first gc head of the
** global gc list ; if called with the NEW option it instead creates a new gc
** head
*/

int		get_gc(t_lst **gc_lst, int opt)
{
	static t_head	global_gc_head = {0, NULL, NULL};
	t_head			*new_gc_head;

	if (global_gc_head.size == 0)
		ft_memset(&global_gc_head, 0, sizeof(global_gc_head));
	if (opt == NEW)
	{
		if (!(new_gc_head = (t_head *)malloc(sizeof(*new_gc_head))))
			return (ERROR_MALLOC);
		else if (!(*gc_lst = (t_lst *)malloc(sizeof(**gc_lst))))
			return (ERROR_MALLOC);
		(*gc_lst)->content = new_gc_head;
		ft_lstadd(&global_gc_head, *gc_lst);
	}
	else
		*gc_lst = global_gc_head.first->content;
	return (EXIT_SUCCESS);
}

/*
** this functions frees the first gc head, list and content of the first gc of
** the global gc list ; if called with the ALL option, it uses tail recursion to
** free all gc heads
*/

void	free_gc(int opt)
{
	t_lst	*gc_lst;
	t_lst	*to_free;
	t_head	*gc_head;

	if (get_gc(&gc_lst, CURRENT) != EXIT_SUCCESS)
		return ;
	gc_head = gc_lst->content;
	if (gc_head->first)
	{
		to_free = gc_head->last->prev;
		while (to_free)
		{
			free(to_free->next->content);
			free(to_free->next);
			to_free = to_free->prev;
		}
		free(gc_head->first->content);
		free(gc_head->first);
		free(gc_head);
	}
	free(gc_lst);
	if (opt == ALL)
		free_gc(ALL);
}

/*
** this function pops and frees the elem from the first gc of the global gc
** list that contains the matching malloc'ed zone
*/

void	easyfree(void **match)
{
	t_lst	*elem;
	t_lst	*gc_lst;
	t_head	*gc;

	if (!EASY || !*match)
		return ;
	if (get_gc(&gc_lst, CURRENT) != EXIT_SUCCESS)
		return ;
	gc = gc_lst->content;
	if (!(elem = ft_lstpop(gc, *match)))
		return ;
	free(elem->content);
	free(elem);
	elem = NULL;
	free(*match);
	*match = NULL;
}

/*
** this function allocs a zone, and stores it in the first gc of the global gc
** list
*/

void	*easymalloc(size_t size)
{
	void	*new_malloc;
	t_lst	*new_gc_elem;
	t_lst	*gc_lst;
	t_head	*gc;

	if (!EASY)
		return (ft_memalloc(size));
	if (size < 1)
		return (0);
	if (get_gc(&gc_lst, CURRENT) != EXIT_SUCCESS)
		return (NULL);
	gc = gc_lst->content;
	if (!(new_gc_elem = (t_lst *)malloc(sizeof(*new_gc_elem))))
		return (NULL);
	else if (!(new_malloc = malloc(size)))
		return (NULL);
	ft_memset(new_malloc, 0, size);
	new_gc_elem->content = new_malloc;
	ft_lstadd(gc, new_gc_elem);
	return (new_malloc);
}
