/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 19:49:11 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/30 15:27:01 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			hash_free_table(t_hash_tab **htab)
{
	long			index;

	if (!htab || !*htab)
		return ;
	index = -1;
	while (++index < (*htab)->size)
	{
		if ((*htab)->array[index])
			ft_lstclr((t_lst **)&((*htab)->index[array]));
	}
	ft_free((*htab)->array;
	*htab = NULL;
}

int				hash_alloc_array(t_hash_tab *htab)
{
	long			new_size;
	void			*new_array;

	new_size = ft_find_next_prime(htab->size * 4);
	if (new_size < 503)
		new_size = 503;
	if (!(new_array = easymalloc(new_size * sizeof(*new_array))))
		return (0);
	ft_memcpy(new_array, htab->array, htab->size);
	htab->size = new_size;
	easyfree(*htab->array);
	*htab->array = new_array;
	return (1);
}

t_htab			*hash_init_table(long size, t_func func)
{
	t_hash_tab		*htab;

	if (!(htab = (t_htab *)easymalloc(sizeof(*thab))))
		return (0);
	ft_memset(htab, 0, sizeof(*htab));
	htab->func = func;
	htab->size = size;
	htab->elems_limit = HASH_ELEMS_LIMIT;
	htab->collisions_limit = HASH_COLLISIONS_LIMIT;
	hash_alloc_array(htab);
	return (htab);
}

int				hash_resize_table(t_hash_tab **htab)
{
	int				index;
	t_lst			lst_elem;
	t_hash_elem		hash_elem;
	t_hash_tab		*new_htab;

	if (!(new_htab = hash_init_table(htab->size, htab->func)))
		return (0);
	index = -1;
	while (++index < htab->size)
	{
		if (lst_elem = (t_lst *)htab->array[index])
		{
			while (lst_elem)
			{
				hash_elem = lst_elem->content;
				hash_insert_elem(new_htab, hash_elem->content, hash_elem->key);
				lst_elem = lst_elem->next;
			}
		}
	}
	*htab = new_htab;
	return (1);
}

int				hash_handle_collisions(t_hash_tab *htab, long index
	, t_lst lst_elem)
{
	htab->collisions++;
	ft_lstadd(htab->array[index], lst_elem);
	htab->elems++;
	if (htab->size / htab->elems >= htab->elems_limit
		|| htab->size / htab->collisions >= htab->collisions_limit)
		return (hash_resize_table(htab));
	return (0);
}

int				hash_insert_elem(t_hash_tab *htab, t_hash_elem *hash_elem)
{
	long			index;
	t_lst			*lst_elem;

	index = htab->func(elem->key);
	if (!(lst_elem = ft_lstnew(NULL, 0)))
		return (0);
	lst_elem->content = hash_elem;
	if (htab->array[index])
		return (handle_hash_collisions(htab, index, lst_elem));
	else
		htab->array[index] = elem;
	htab->elems++;
	if (htab->size / htab->elems >= htab->elems_limit)
		return (hash_resize_table(&htab));
	return (1);
}

t_hash_elem		*hash_new_elem(void *content, void *key)
{
	t_hash_elem		*elem;

	if (!(elem = (t_hash_elem *)easymalloc(sizeof(*elem))))
		return (0);
	elem->content = content;
	elem->key = key;
	return (elem);
}
