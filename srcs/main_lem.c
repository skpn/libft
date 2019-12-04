/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:05:02 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/04 22:23:58 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lem_in.h"

int		main(void)
{
	t_lem	*lem;

	if (!(init_lem(&lem)))
		return (exit_lem(lem, "init failed\n", 1));
	PRINTPOSN;
	if (!parse_input(lem))
		return (exit_lem(lem, "ERROR", 2));
	PRINTPOSN;
	if (!set_graph(lem))
	{
		printf("BEFORE EXIT, ROOMS:\n");
		print_rooms(lem->rooms);
		return (exit_lem(lem, "ERROR", 2));
	}
	PRINTPOSN;
//	print_lem(lem, "ar");
	return (0);
}
