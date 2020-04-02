/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage_collector.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:22:22 by skpn              #+#    #+#             */
/*   Updated: 2020/03/30 09:33:49 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GARBAGE_COLLECTOR_H
# define FT_GARBAGE_COLLECTOR_H

# define GC_CURRENT 1
# define GC_NEW 2
# define GC_ALL 3
# define GC_ON 4
# define GC_OFF 8
# define GC_STATE 16
# define GC_FREE 32

# include "ft_lst.h"

void				*easymalloc(size_t size);
void				easyfree(void **match);

void				free_gc(int opt);

int					get_gc(t_lst **gc_lst, int opt);

#endif