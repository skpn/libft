/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:05:02 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/13 17:08:31 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lem_in.h"
#include <fcntl.h>

int		main(void)
{
	t_lem	*lem;

	g_fd = open("debug", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	dprintf(g_fd, "%s %d\n", __func__, __LINE__);
	if (!(init_lem(&lem)))
		return (exit_lem(lem, "init failed\n", 1));
	PRINTPOSN;
	if (!parse_input(lem))
		return (exit_lem(lem, "ERROR", 2));
	PRINTPOSN;
	if (!set_graph(lem))
	{
		printf("BEFORE EXIT, ROOMS:\n");
		//print_rooms(lem->rooms);
		return (exit_lem(lem, "ERROR", 2));
	}
	if (!seek_paths(lem))
	{
		return (exit_lem(lem, "ERROR", 2));
	}
	PRINTPOSN;
	return (0);
}
