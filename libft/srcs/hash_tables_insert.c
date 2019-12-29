
#include "libft.h"

void		transfer_hash_elems(t_h_table *table, unsigned new_size
		, unsigned old_size, t_head *old_array)
{
	unsigned	index;
	t_head		*old_index_head;
	t_head		*rehashed_index_head;
	t_lst		*transfer;
	t_h_elem	*hash_elem;

	index = 0;
	while (index < old_size)
	{
		old_index_head = &(old_array[index]);
		while (old_index_head->first)
		{
			transfer = ft_lstpop(old_index_head, old_index_head->first);
			hash_elem = transfer->content;
			rehashed_index_head = &(table->array[hash_elem->hash % new_size]);
			ft_lstadd(rehashed_index_head, transfer);
		}
		index++;
	}
}

int			ft_hash_resize_array(t_h_table *table, unsigned new_size)
{
	t_head	*old_array;

	old_array = table->array;
	if (!(table->array = (t_head *)easymalloc(sizeof(t_head) * new_size)))
	{
		table->array = old_array;
		return (0);
	}
	if (old_array)
	{
		transfer_hash_elems(table, new_size, table->size, old_array);
	}
	easyfree((void **)&old_array);
	table->size = new_size;
	table->collisions_limit = table->size / COLLISIONS_REJECTION_FACTOR;
	if (table->collisions_limit < 1)
		table->collisions_limit = 1;
	return (1);
}

int				insert_hash_elem(t_h_table *table, unsigned index
		, t_h_elem *new_elem)
{
	unsigned	new_size;
	t_head		*index_head;

	index_head = &(table->array[index]);
	if (!(ft_lstadd_new(index_head, new_elem)))
		return (0);
	if (index_head->size > 1)
	{
		table->collisions++;
		if (table->collisions > table->collisions_limit)
		{
			new_size = ft_find_next_prime(table->size);
			return (ft_hash_resize_array(table, new_size));
		}
	}
	return (1);
}

int			ft_hash_add_elem(t_h_table *table, char *key, void *content)
{
	unsigned	index;
	t_h_elem	*new_elem;

	if (!(new_elem = (t_h_elem *)easymalloc(sizeof(*new_elem))))
		return (0);
	new_elem->hash = table->hash_func(key);
	new_elem->content = content;
	new_elem->key = key;
	index = new_elem->hash % table->size;
	if (!insert_hash_elem(table, index, new_elem))
	{
		easyfree((void **)new_elem);
		return (0);
	}
	return (1);
}
