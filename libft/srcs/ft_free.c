/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfree_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:04:30 by sikpenou          #+#    #+#             */
/*   Updated: 2019/04/22 11:07:10 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_free(void **ptr)
{
	if (!*ptr)
		return ;
	EASY ? easyfree((void **)ptr) : free((void **)ptr);
	*ptr = NULL;
	return ;
}
