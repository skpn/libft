/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tables_insert.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:48:23 by sikpenou          #+#    #+#             */
/*   Updated: 2020/03/27 11:20:36 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** this file manages element insertions, and monitors the table's state and
** resizes it if the number of collisions gets too high
** the key for an element must be a string, and if it is malloc'ed it must not
** be freed while the element is part of the table
** you can adjust the collisions rejection factors (the higher you set it, the
** less collisions are accepted) and the initial table size in the libft.h file,
** and resize the table yourself with the ft_h_resize_array function
*/

/*
** this function pops each element from its index's list, and uses its hash to
** add it to the correct new index
** hashes are never erased, so redispatching the elements only takes a modulo
** operation and a list add
*/

static void	transfer_hash_array(t_h_table *table, unsigned new_size
		, unsigned old_size, t_head *old_array)
{
	unsigned	index;
	t_head		*index_head;
	t_head		*rehashed_index_head;
	t_lst		*transfer;
	t_h_elem	*hash_elem;

	index = 0;
	while (index < old_size)
	{
		index_head = &(old_array[index]);
		while (index_head->first)
		{
			transfer = ft_lstpop(index_head, index_head->first->content);
			hash_elem = transfer->content;
			rehashed_index_head = &(table->array[hash_elem->hash % new_size]);
			if (rehashed_index_head->size > 0)
				table->collisions++;
			ft_lstadd(rehashed_index_head, transfer);
		}
		index++;
	}
}

int			ft_h_resize_array(t_h_table *table, unsigned new_size)
{
	t_head	*old_array;

	old_array = table->array;
	if (!(table->array = (t_head *)easymalloc(sizeof(t_head) * new_size)))
	{
		table->array = old_array;
		return (EXIT_FAILURE);
	}
	if (old_array)
	{
		table->collisions = 0;
		transfer_hash_array(table, new_size, table->size, old_array);
	}
	easyfree((void **)&old_array);
	table->size = new_size;
	table->collisions_limit = table->size / COLLISIONS_REJECTION_FACTOR;
	if (table->collisions_limit < 1)
		table->collisions_limit = 1;
	return (EXIT_SUCCESS);
}

static int	insert_hash_elem(t_h_table *table, unsigned index
		, t_h_elem *new_elem)
{
	unsigned	new_size;
	t_head		*index_head;

	index_head = &(table->array[index]);
	if (!(ft_lstadd_new(index_head, new_elem)))
		return (EXIT_FAILURE);
	if (index_head->size > 1)
	{
		table->collisions++;
		while (table->collisions > table->collisions_limit)
		{
			new_size = ft_find_next_prime(table->size * 3 + 1);
			return (ft_h_resize_array(table, new_size));
		}
	}
	return (EXIT_SUCCESS);
}

static int	str_key_is_unique(t_h_table *table, char *key)
{
	unsigned	index;
	t_h_elem	*hash_elem;
	t_lst		*index_lst;

	index = table->func_hash(key);
	index_lst = table->array[index].first;
	while (index_lst)
	{
		hash_elem = index_lst->content;
		if (!ft_strcmp(hash_elem->key, key))
			return (EXIT_FAILURE);
		index_lst = index_lst->next;
	}
	return (EXIT_SUCCESS);
}

/*
** add elem creates the actual hash elements and points it to the content but
** the actual insertion is managed in insert_hash_elem
*/

int			ft_h_add_elem(t_h_table *table, char *key, void *content)
{
	unsigned	index;
	t_h_elem	*new_elem;

	if (str_key_is_unique(table, key) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (!(new_elem = (t_h_elem *)easymalloc(sizeof(*new_elem))))
		return (EXIT_FAILURE);
	if (!(new_elem->key = ft_strdup(key)))
		return (EXIT_FAILURE);
	new_elem->hash = table->func_hash(key);
	new_elem->content = content;
	index = new_elem->hash % table->size;
	if (insert_hash_elem(table, index, new_elem) != EXIT_SUCCESS)
	{
		ft_h_free_elem(table, new_elem, FREE_STRUCT);
		return (EXIT_FAILURE);
	}
	table->elems++;
	return (EXIT_SUCCESS);
}
