/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_tables.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:18:04 by skpn              #+#    #+#             */
/*   Updated: 2020/03/27 10:56:23 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HASH_TABLES_H
# define FT_HASH_TABLES_H

# define INITIAL_HASH_ARRAY_SIZE 4999
# define COLLISIONS_REJECTION_FACTOR 10

#include "ft_lst.h"

typedef struct		s_h_elem
{
	unsigned		hash;
	char			*key;
	void			*content;
}					t_h_elem;

typedef int			(*t_func_h_iter)(t_h_elem *);
typedef void		(*t_func_h_print)(t_h_elem *);
typedef unsigned	(*t_func_h_hash)(void *);
typedef void		(*t_func_h_free)(void **);

typedef struct		s_h_table
{
	unsigned		size;
	unsigned		elems;
	unsigned		collisions;
	unsigned		collisions_limit;
	t_func_h_hash	func_hash;
	t_func_h_free	func_free;
	t_func_h_print	func_print;
	t_head			*array;
}					t_h_table;

int					ft_h_add_elem(t_h_table *table, char *key, void *content);
t_h_table			*ft_h_alloc_new_table(void);

void				ft_h_free_elem(t_h_table *table, t_h_elem *h_elem, int opt);
void				ft_h_free_table(t_h_table *table, int opt);

void				*ft_h_get_content(t_h_table *table, char *key);
t_h_elem			*ft_h_get_elem(t_h_table *table, char *key);

int					ft_h_iter(t_h_table *table, t_func_h_iter iter_func);
int					ft_h_init_table(t_h_table *table);

t_h_elem			*ft_h_pop_elem(t_h_table *table, char *key);

int					ft_h_resize_array(t_h_table *table,
	unsigned new_size);

void				h_print_index(t_h_table *table, unsigned index, int opt);
void				h_print_table(t_h_table *table, int opt);
void				h_print_table_data(t_h_table *table);

void				h_elem_print(t_h_elem *elem);
void				h_elem_free(void **elem);

#endif