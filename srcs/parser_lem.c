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

int		get_anthill(t_lem *lem)
{
	char	*line;
	int		ret;

	line = 0;
	while ((ret = filler_gnl(0, &line) > 0))
		if (*line != '#' || line[1] == '#')
			ft_strjoin_free(lem->anthill, line, 3);
	return (ret ? 0 : 1);
}

int		parse_input(t_lem *lem)
{
	if (!(get_anthill(lem)))
		return (0);
	print_anthill(lem);
	return (1);
}
