/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_gnl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 18:42:27 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/19 19:00:54 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"
#include <stdlib.h>
#include <unistd.h>

int		lem_realloc(char **zone, unsigned curr_size, long to_add)
{
	char	*tmp;

	if (!(tmp = (char *)malloc(sizeof(char) * (curr_size + to_add))))
		return (0);
	ft_memcpy(tmp, *zone, curr_size);
	easyfree((void **)zone);
	*zone = tmp;
	return (curr_size + to_add);
}

int		get_anthill(t_lem *lem)
{
	unsigned	curr_size;
	int			ret;

	if (!(lem->anthill = (char *)malloc(LEM_BUFF + 1)))
		return (0);
	curr_size = LEM_BUFF + 1;
	lem->anthill[LEM_BUFF] = 0;
	while ((ret = read(0, lem->anthill, LEM_BUFF)) >= 0 && curr_size < MAX_SIZE)
	{
		lem->anthill[ret] = 0;
		if (ret == LEM_BUFF)
		{
//			printf("before realloc, anthill: %s\n", lem->anthill);
			if (!(curr_size = lem_realloc(&lem->anthill, curr_size, LEM_BUFF)))
				return (0);
		}
		else
		{
			if (!(lem->copy = (char *)malloc(curr_size + 1)))
				return (0);
//			printf("before copy, anthill: %s\n", lem->anthill);
			ft_strcpy(lem->copy, lem->anthill);
			return (1);
		}
	}
	return (0);
}
