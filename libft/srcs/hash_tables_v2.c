
#include "libft.h"

int			hash_rehash_array(t_h_table *h_table, t_head **new_array
	, unsigned new_size)
{
	unsigned	cell;
	t_lst		*h_lst_elem;
	t_lst		*transfer_elem;
	t_h_elem	*h_elem;

	cell = 0;
	while (cell < h_table->size)
	{
		h_lst_elem = h_table->array[cell]->first;
		while (h_lst_elem)
		{
			h_elem = h_lst_elem->content;
			h_lst_elem = h_lst_elem->next;
			;
		}
	}
}

int			hash_resize_table(t_h_table *h_table)
{
	unsigned	new_size;
	unsigned	cell;
	t_head		**new_array;

	new_size = ft_find_next_prime(h_table->size);
	if (!(new_array = (t_head **)easymalloc(sizeof(t_head *) * new_size)))
		return (NULL);
	if (!hash_rehash_array(new_array, h_table))
		return (0);
	easyfree((void **)h_table->array);
	h_table->size = new_size
}

t_h_table	*hash_alloc_table(t_h_func *h_func)
{
	t_h_table	*new_table;

	if (!(new_table = (t_h_table *)easymalloc(sizeof(*new_table))))
		return (NULL);
	if (!(new_table->array = (t_head **)easymalloc(sizeof(t_head *) * 503)))
		return (NULL);
	new_table->size = 503;
	new_table->elems_limit = new_table->;
	new_table->collisions_limit = HASH_COLLISIONS_LIMIT;
	new_table->h_func = h_func;
}
