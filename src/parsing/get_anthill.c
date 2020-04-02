/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_anthill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 13:18:41 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/13 15:55:18 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "lem_in.h"

static int		lem_realloc(char **zone, unsigned curr_size, long to_add)
{
	char	*tmp;

	if (!(tmp = (char *)malloc(sizeof(char) * (curr_size + to_add))))
		return (0);
	ft_memcpy(tmp, *zone, curr_size);
	easyfree((void **)zone);
	*zone = tmp;
	return (curr_size + to_add);
}

static int		read_loop(t_lem *lem, unsigned curr_size)
{
	int		ret;

	while ((ret = read(0, lem->anthill + lem->anthill_size, LEM_BUFF)) >= 0
		&& curr_size < MAX_SIZE)
	{
		lem->anthill_size += ret;
		if (ret == LEM_BUFF)
		{
			if (!(curr_size = lem_realloc(&lem->anthill, curr_size, LEM_BUFF)))
				return (0);
		}
		else
		{
			if (!(lem->copy = (char *)malloc(curr_size + 1)))
				return (0);
			lem->anthill[lem->anthill_size] = '\n';
			lem->anthill[lem->anthill_size + 1] = '\0';
			ft_strcpy(lem->copy, lem->anthill);
			return (1);
		}
	}
	lem->anthill[lem->anthill_size] = 0;
	return (0);
}

int				get_anthill(t_lem *lem)
{
	unsigned	curr_size;

	if (!(lem->anthill = (char *)malloc(LEM_BUFF + 2)))
		return (0);
	curr_size = LEM_BUFF + 2;
	lem->anthill[LEM_BUFF] = 0;
	lem->anthill[LEM_BUFF + 1] = 0;
	return (read_loop(lem, curr_size));
}
