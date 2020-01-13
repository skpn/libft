/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:28:02 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/10 14:25:31 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

int		manage_start_end(t_lem *lem, char *anthill, int *opt)
{
	if (*opt == REJECT_START_END
		&& (!ft_strncmp(anthill + lem->pos, "start\n", 6)
		|| !ft_strncmp(anthill + lem->pos, "end\n", 4)))
		return (PARSING_ERROR);
	else if (!ft_strncmp(anthill + lem->pos, "start\n", 6))
	{
		if (lem->start)
			return (PARSING_ERROR);
		*opt = START;
		lem->pos += 6;
	}
	else if (!ft_strncmp(anthill + lem->pos, "end\n", 4))
	{
		if (lem->end)
			return (PARSING_ERROR);
		*opt = END;
		lem->pos += 4;
	}
	else
	{
		while (anthill[lem->pos] && anthill[lem->pos++] != '\n')
			;
	}
	return (1);
}

int		manage_com(t_lem *lem, char *anthill, int *opt)
{
	if (anthill[++lem->pos] == '#')
	{
		lem->pos++;
		return (manage_start_end(lem, anthill, opt));
	}
	while (anthill[lem->pos] && anthill[lem->pos++] != '\n')
		;
	return (1);
}

int		get_ants(t_lem *lem, char *anthill)
{
	int		check_startend;

	if (lem->nb_ants)
		return (0);
	check_startend = REJECT_START_END;
	if (anthill[lem->pos] == '#')
		return (manage_com(lem, anthill, &check_startend));
	while (anthill[lem->pos] >= '0' && anthill[lem->pos] <= '9')
		lem->nb_ants = lem->nb_ants * 10 + anthill[lem->pos++] - '0';
	if (anthill[lem->pos] != '\n' || !anthill[lem->pos++])
		return (PARSING_ERROR);
	return (1);
}

int		check_input(t_lem *lem)
{
	if (lem->start == NULL || lem->end == NULL
		|| !lem->nb_ants || !lem->table->elems)
		return (-1);
	return (1);
}

int		parse_input(t_lem *lem)
{
	int			ret;

	if (!get_anthill(lem))
		return (MALLOC_ERROR);
	while ((ret = get_ants(lem, lem->copy)) > 0)
		;
	if (!lem->nb_ants)
		return (PARSING_ERROR);
	if (ret < 0)
		return (ret);
	while ((ret = get_rooms(lem, lem->copy)) > 0)
		;
	if (ret < 0 || (!lem->start) || (!lem->end))
		return (ret);
	while ((ret = get_tubes(lem, lem->copy)) > 0)
		;
	if (ret < 0)
		return (ret);
	while (lem->anthill[lem->pos])
		lem->pos++;
	return (1);
}
