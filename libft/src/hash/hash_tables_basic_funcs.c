/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tables_basic_funcs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 09:51:54 by skpn              #+#    #+#             */
/*   Updated: 2020/03/25 12:41:01 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** if your elements contain structures with multiple variables patterns you can
** modify the alloc/print/free functions or directly reassign your own functions
** to the table's function pointer variables (you may have to modify the header
** file typedefs to accomodate your function prototypes)
*/

void	h_elem_print(t_h_elem *elem)
{
	ft_printf("printing hash elem %p\nkey    : %s\nhash   : %u, content: %p\n"
			, elem, elem->key, elem->hash, elem->content);
}

void	h_elem_free(void **content)
{
	easyfree((void **)content);
}
