/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:43:11 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/26 12:28:25 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		ft_realloc(char **zone, long curr_size, long to_add)
{
	char	*tmp;

	if (!(tmp = (char *)easymalloc(curr_size + to_add)))
		return (ERROR_MALLOC);
	ft_memcpy(tmp, *zone, curr_size);
	easyfree((void **)zone);
	*zone = tmp;
	return (EXIT_SUCCESS);
}
