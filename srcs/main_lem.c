/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:05:02 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/19 19:03:42 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lem_in.h"
#include <fcntl.h>

int		main(void)
{
	t_lem	*lem;

	
//	g_fd = open("debug", O_WRONLY | O_TRUNC | O_CREAT, 0644);
//	g_fd_alloc = open("alloc_log", O_WRONLY | O_TRUNC | O_CREAT, 0644);
//	g_fd_free = open("free_log", O_WRONLY | O_TRUNC | O_CREAT, 0644);
//	dprintf(g_fd, "%s %d\n", __func__, __LINE__);
	//sleep(10);
	if (!(lem = alloc_new_lem()))
		return (exit_lem(&lem, "init failed\n", 1));
	if (parse_input(lem) <= 0)
	{
		//printf("ret parse input < 0\n");
		return (exit_lem(&lem, "ERROR\n", 2));
	}
	hash_print_table(lem->table, QUIET);
//	printf("%p\n", lem->start);
//	print_rooms(lem->rooms);
//	return (0);
	if (set_graph(lem) <= 0)
	{
		//printf("BEFORE EXIT, ROOMS:\n");
		//print_rooms(lem->rooms);
		return (exit_lem(&lem, "ERROR\n", 2));
	}
	if (lem->end->dist == 1)
	{
		start_joined_to_end(lem);
	}
	else
	{
		if (!seek_paths(lem))
			return (exit_lem(&lem, "ERROR\n", 2));
			//		printf("\nSORTIE DE L'ALGO, config->first =\n");
			//		print_config(lem->config_lst->first->content);
		else if (!display_lem(lem))
			return (exit_lem(&lem, "ERROR\n", 2));
	}
	exit_lem(&lem, "", 2);
	return (0);
}
