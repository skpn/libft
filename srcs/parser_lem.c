/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:28:02 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/13 15:48:27 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"
#include <stdlib.h>

char	*ft_strjoin_anthill(char **s1, char **s2, int opt)
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
		dprintf(g_fd, "malloc for joinanthill\n");
		if (!(new = (char *)easymalloc(len1 + len2 + 2)))
			return (NULL);
		ft_strcpy(new, *s1);
		ft_strcpy(new + len1, *s2);
		*(new + len1 + len2) = '\n';
	}
	else if (*s1 || *s2)
		new = *s1 ? ft_strjoin_anthill(s1, &backn, LEFT)
			: ft_strjoin_anthill(s2, &backn, 0);
	opt == BOTH || opt == LEFT ? dprintf(g_fd, "join anthill free s1\n") : 0;
	opt == BOTH || opt == LEFT ? ft_free((void **)s1) : 0;
	opt == BOTH || opt == RIGHT ? dprintf(g_fd, "join anthill free s2\n") : 0;
	opt == BOTH || opt == RIGHT ? ft_free((void **)s2) : 0;
	return (new);
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
		if (!(lem->anthill = ft_strjoin_anthill(&(lem->anthill), &line, LEFT)))
			return (-1);
	}
	dprintf(g_fd, "freeing line after read\n");
	ft_free((void **)&line);
	lem->shortest = 0xFFFFFFFF;
	lem->max_dist = 0xFFFFFFFF;
	return (ret ? 0 : 1);
}
