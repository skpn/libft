/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:28:02 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/24 15:51:17 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"
#include <stdlib.h>

static void	init_tab(int (*tab[3])(t_lem *, char **, int *))
{
	tab[0] = parse_ants;
	tab[1] = parse_room;
	tab[2] = parse_tube;
}

int		get_anthill(t_lem *lem)
{
	char	*line;
	int		ret;
	int		index;
	int		(*tab[3])(t_lem *, char **, int *);

	line = 0;
	init_tab(tab);
	index = 0;
	while ((ret = filler_gnl(0, &line) > 0))
	{
			if (!(tab[index](lem, &line, &index)))
				return (-1);
	}
	return (ret ? 0 : 1);
}

int		parse_input(t_lem *lem)
{
	if (!(get_anthill(lem)))
		return (0);
	print_lem(lem, "aser");
	return (1);
}
