/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:28:02 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/14 18:40:42 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"
#include <stdlib.h>

char	*ft_strjoin_anthill(char **s1, char **s2)
{
	int		len1;
	int		len2;
	char	*new;
	char	*backn;

	new = NULL;
	backn = "\n";
	if (*s1 && *s2)
	{
		len1 = ft_strlen(*s1);
		len2 = ft_strlen(*s2);
		if (!(new = (char *)easymalloc(len1 + len2 + 2)))
			return (NULL);
		ft_strcpy(new, *s1);
		ft_strcpy(new + len1, *s2);
		*(new + len1 + len2) = '\n';
	}
	else if (*s1 || *s2)
		new = *s1 ? ft_strjoin_anthill(s1, &backn)
			: ft_strjoin(*s2, backn);
	easyfree((void **)s1);
	return (new);
}

int		check_input(t_lem *lem)
{
	if (lem->start == NULL || lem->end == NULL || !lem->nb_ants ||
		!lem->nb_rooms)
	{
//		printf("CHECK INPUT RETURNS 0");
		return (0);
	}
	return (1);
}

int		parse_input(t_lem *lem)
{
	char	*line;
	int		ret;
	int		index;
	int		(*tab[3])(t_lem *, char **, int *);

	line = 0;
	tab[0] = parse_ants;
	tab[1] = parse_room;
	tab[2] = parse_tube;
	index = 0;
	while ((ret = gnl_lem_in(0, &(lem->shortest), &(lem->max_dist), &line) > 0))
	{
		if (!(tab[index](lem, &line, &index)))
			return (-1);
		if (!(lem->anthill = ft_strjoin_anthill(&(lem->anthill), &line)))
			return (-1);
	}
	easyfree((void **)&line);
	lem->shortest = 0xFFFFFFFF;
	lem->max_dist = 0xFFFFFFFF;
	if (ret)
		return (0);
	if (!check_input(lem))
		return (0);
	return (1);
}
