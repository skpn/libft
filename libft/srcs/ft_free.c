/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfree_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:04:30 by sikpenou          #+#    #+#             */
/*   Updated: 2019/11/05 23:41:03 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_free(void **ptr)
{
	printf("in ft_free freeing *ptr: %p\n", *ptr);
	if (!*ptr)
		return ;
	if (EASY)
		easyfree((void **)ptr);
	else
		free(*ptr);
	*ptr = NULL;
}
