/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:49:38 by sikpenou          #+#    #+#             */
/*   Updated: 2020/03/29 10:34:08 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*newzone;

	if (!size)
		return (NULL);
	newzone = easymalloc(size);
	if (!(newzone))
		return (NULL);
	ft_memset(newzone, 0, size);
	return (newzone);
}
