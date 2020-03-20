/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tables_memory.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:48:39 by sikpenou          #+#    #+#             */
/*   Updated: 2020/03/20 19:04:36 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** this is the alloc / free file for hash tables
*/

void			ft_h_free_elem(t_h_table *table, t_h_elem *hash_elem
	, int opt)
{
	if (opt != FREE_LINKS)
		table->func_free(&(hash_elem->content));
	easyfree((void **)&hash_elem);
}

void			ft_h_free_table(t_h_table *table, int opt)
{
	unsigned	index;
	t_head		*index_head;
	t_lst		*index_lst;

	index = 0;
	while (index < table->size)
	{
		if (table->array[index].first)
		{
			index_head = &(table->array[index]);
			while (index_head->first)
			{
				index_lst = ft_lstpop_elem(index_head, index_head->first);
				ft_h_free_elem(table, index_lst->content, opt);
				ft_lstfree_elem(&index_lst, FREE_LINKS);
			}
		}
		index++;
	}
	easyfree((void **)&table->array);
	easyfree((void **)&table);
}

/*
** you can change the key type and hash method directly in this function, or
** reassign your own function to the table->func_hash variable
*/

static unsigned	h_hash_str(void *void_key)
{
	unsigned	hash;
	char		*key;

	hash = 0;
	key = (char *)void_key;
	while (*key)
	{
		hash = hash * 97 + *key;
		key++;
	}
	return (hash);
}

/*
** if your elements contain structures with complex freeing patterns you can
** modify the h_elem_free function or directly reassign your own function to the
** t_h_table func_free variable
*/

static void		h_elem_free(void **content)
{
	easyfree((void **)content);
}

/*
** the core of the table is an array of t_head structs (not pointers, to avoid
** having to manage each index in memory)
** it starts empty and is immediately resized
*/

t_h_table		*ft_h_new_table(void)
{
	t_h_table	*new_table;
	unsigned	size;

	if (!(new_table = (t_h_table *)easymalloc(sizeof(*new_table))))
		return (0);
	new_table->func_hash = &h_hash_str;
	new_table->func_free = &h_elem_free;
	new_table->func_print = &h_elem_print;
	size = ft_find_next_prime(INITIAL_HASH_ARRAY_SIZE);
	if (!ft_h_resize_array(new_table, size))
		return (NULL);
	return (new_table);
}
