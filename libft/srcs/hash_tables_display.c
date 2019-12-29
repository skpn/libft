
#include "../includes/libft.h"

void		hash_print_elem(t_h_elem *elem)
{
	printf("printing hash elem %p\nkey    : %s\nhash   : %u, content: %p\n"
			, elem, elem->key, elem->hash, elem->content);
}

void		hash_print_index(t_h_table *table, unsigned index, int opt)
{
	t_head	*index_head;
	t_lst	*hash_elem_lst;

	index_head = &(table->array[index]);
	hash_elem_lst = index_head->first;
	if (hash_elem_lst)
	{
		printf("table %p, index %u (%p):\n", table, index, index_head);
		while (hash_elem_lst)
		{
			hash_print_elem(hash_elem_lst->content);
			hash_elem_lst = hash_elem_lst->next;
		}
	}
	else if (opt == VERBOSE)
		printf("table %p, index %u (%p): index empty\n", table, index,
			index_head);
}

void		hash_print_table(t_h_table *table, int opt)
{
	unsigned	index;

	index = 0;
	printf("printing hash table %p\nsize : %u\ncoll : %u\nlimit: %u\n"
			, table, table->size, table->collisions, table->collisions_limit);
	while (index < table->size)
	{
		hash_print_index(table, index, opt);
		index++;
	}
}

