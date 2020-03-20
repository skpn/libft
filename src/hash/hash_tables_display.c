/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tables_display.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:47:51 by sikpenou          #+#    #+#             */
/*   Updated: 2020/03/19 19:07:32 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** this is a small set of simple display functions
** if your elements contain structures with complex printing patterns you can
** modify the h_elem_free function or directly reassign your own function to the
** t_h_table func_free variable
*/

void	h_elem_print(t_h_elem *elem)
{
	ft_printf("printing hash elem %p\nkey    : %s\nhash   : %u, content: %p\n"
			, elem, elem->key, elem->hash, elem->content);
}

void	hash_print_index(t_h_table *table, unsigned index, int opt)
{
	t_head	*index_head;
	t_lst	*hash_elem_lst;

	index_head = &(table->array[index]);
	hash_elem_lst = index_head->first;
	if (hash_elem_lst)
	{
		ft_printf("table %p, index %u (%p):\n", table, index, index_head);
		while (hash_elem_lst)
		{
			table->func_print(hash_elem_lst->content);
			hash_elem_lst = hash_elem_lst->next;
		}
		ft_printf("\n");
	}
	else if (opt == VERBOSE)
	{
		ft_printf("table %p, index %u (%p): index empty\n", table, index,
			index_head);
		ft_printf("\n");
	}
}

void	hash_print_table(t_h_table *table, int opt)
{
	unsigned	index;

	index = 0;
	ft_printf("printing hash table %p\nsize : %u\nelems: %u\ncoll : %u\n"
		"limit: %u\n", table, table->size, table->elems, table->collisions
		, table->collisions_limit);
	while (index < table->size)
	{
		hash_print_index(table, index, opt);
		index++;
	}
}

void	hash_print_table_data(t_h_table *table)
{
	ft_printf("printing hash table %p\nsize : %u\nelems: %u\ncoll : %u\n"
		"limit: %u\n", table, table->size, table->elems, table->collisions
		, table->collisions_limit);
}
