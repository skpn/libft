/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 13:17:30 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/03 17:15:56 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

int		check_enough_info(t_lem *lem)
{
	if (lem->start && lem->end)
		return (1);
	return (0);
}

int		main(void)
{
	t_lem	*lem;
	int		ret;

	if (!(lem = alloc_new_lem()))
		return (exit_lem(&lem, "init failed\n", 1));
	if ((ret = parse_input(lem)) == MALLOC_ERROR)
		return (exit_lem(&lem, "ERROR\n", 2));
	if (!check_enough_info(lem))
		return (exit_lem(&lem, "ERROR\n", 2));
	if (set_graph(lem) <= 0)
		return (exit_lem(&lem, "ERROR\n", 2));
	if (lem->end->dist == 1)
		start_joined_to_end(lem);
	else
	{
		if (!seek_paths(lem))
			return (exit_lem(&lem, "ERROR\n", 2));
		if (!display_lem(lem))
			return (exit_lem(&lem, "ERROR\n", 2));
	}
	exit_lem(&lem, "", 2);
	return (0);
}
