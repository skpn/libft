/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tableles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 19:49:11 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/31 09:52:13 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			hash_free_table(t_h_table **h_table)
{
	long			index;

	if (!h_table || !*h_table)
		return ;
	index = -1;
	while (++index < (*h_table)->size)
	{
		if ((*h_table)->array[index])
			ft_lstclr((t_lst **)&((*h_table)->index[array]));
	}
	ft_free((*h_table)->array;
	*h_table = NULL;
}

int				hash_alloc_array(t_h_table *h_table)
{
	long			new_size;
	void			*new_array;

	new_size = ft_find_next_prime(h_table->size * 4);
	if (new_size < 503)
		new_size = 503;
	if (!(new_array = easymalloc(new_size * sizeof(*new_array))))
		return (0);
	if (h_table->array)
	{
		ft_memcpy(new_array, h_table->array, h_table->size);
		easyfree(*h_table->array);
	}
	h_table->size = new_size;
	h_table->array = new_array;
	return (1);
}

t_h_table			*hash_init_table(long size, t_func func)
{
	t_h_table		*h_table;

	if (!(h_table = (t_h_table *)easymalloc(sizeof(*h_table))))
		return (0);
	ft_memset(h_table, 0, sizeof(*h_table));
	h_table->func = func;
	h_table->size = size;
	h_table->elems_limit = HASH_ELEMS_LIMIT;
	h_table->collisions_limit = HASH_COLLISIONS_LIMIT;
	hash_alloc_array(h_table);
	return (h_table);
}

int				hash_resize_table(t_h_table **h_table)
{
	int				index;
	t_lst			*lst_elem;
	t_lst			*lst_tmp;
	t_h_elem		hash_elem;
	t_h_table		*new_table;

	if (!(new_table = hash_init_table(h_table->size, h_table->func)))
		return (0);
	index = -1;
	while (++index < h_table->size)
	{
		if (lst_elem = (t_lst *)h_table->array[index])
		{
			while (lst_elem)
			{
				hash_elem = lst_elem->content;
				hash_insert_elem(new_table, hash_elem->content, hash_elem->key);
				lst_tmp = lst_elem->next;
				ft_free((void **)&lst_elem);
				lst_elem = lst_tmp;
			}
		}
	}
	ft_free((void **)&h_table->array);
	ft_free((void **)h_table);
	*h_table = new_table;
	return (1);
}

int				hash_handle_collisions(t_h_table *h_table, long index
	, t_lst lst_elem)
{
	h_table->collisions++;
	ft_lstadd(h_table->array[index], lst_elem);
	h_table->elems++;
	if (h_table->size / h_table->elems >= h_table->elems_limit
		|| h_table->size / h_table->collisions >= h_table->collisions_limit)
		return (hash_resize_table(h_table));
	return (1);
}

int				hash_insert_elem(t_h_table *h_table, t_h_elem *hash_elem)
{
	long			index;
	t_lst			*lst_elem;

	index = h_table->func(elem->key);
	if (!(lst_elem = ft_lstnew(NULL, 0)))
		return (0);
	lst_elem->content = hash_elem;
	if (h_table->array[index])
		return (handle_hash_collisions(h_table, index, lst_elem));
	else
		h_table->array[index] = elem;
	h_table->elems++;
	if (h_table->size / h_table->elems >= h_table->elems_limit)
		return (hash_resize_table(&h_table));
	return (1);
}

t_h_elem		*hash_new_elem(void *content, void *key)
{
	t_h_elem		*elem;

	if (!(elem = (t_h_elem *)easymalloc(sizeof(*elem))))
		return (0);
	elem->content = content;
	elem->key = key;
	return (elem);
}

int				hash_create_elem(content, key)
{
}
