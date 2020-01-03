/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:05:02 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/03 12:15:38 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lem_in.h"
#include <fcntl.h>

int		check_enough_info(t_lem *lem)
{
	// Si parsing error alors il faut checker si on a assez de 
	// contenu pour lancer l'algo
	// genre il faut un start, un end
	// sinon en soit c'est peut etre tout pq l'algo est protégé
	// contre les maps sans chemin valide
	if (lem->start && lem->end)
		return (1);
	return (0);
}

int		main(void)
{
	t_lem	*lem;
	int		ret;

	
//	g_fd = open("debug", O_WRONLY | O_TRUNC | O_CREAT, 0644);
//	g_fd_alloc = open("alloc_log", O_WRONLY | O_TRUNC | O_CREAT, 0644);
//	g_fd_free = open("free_log", O_WRONLY | O_TRUNC | O_CREAT, 0644);
//	dprintf(g_fd, "%s %d\n", __func__, __LINE__);
	//sleep(10);
	if (!(lem = alloc_new_lem()))
		return (exit_lem(&lem, "init failed\n", 1));
	PRINTPOSN;
	if ((ret = parse_input(lem)) == MALLOC_ERROR
		|| (ret == PARSING_ERROR && !check_enough_info(lem)))
		return (exit_lem(&lem, "ERROR\n", 2));
	PRINTPOSN;
//	hash_print_table(lem->table, QUIET);
//	printf("%p\n", lem->start);
//	return (0);
	if (set_graph(lem) <= 0)
	{
		return (exit_lem(&lem, "ERROR\n", 2));
	}
	PRINTPOSN;
	if (lem->end->dist == 1)
	{
	PRINTPOSN;
		start_joined_to_end(lem);
	}
	else
	{
	PRINTPOSN;
		if (!seek_paths(lem))
			return (exit_lem(&lem, "ERROR\n", 2));
	PRINTPOSN;
		if (!display_lem(lem))
			return (exit_lem(&lem, "ERROR\n", 2));
	PRINTPOSN;
	}
	PRINTPOSN;
	exit_lem(&lem, "", 2);
	PRINTPOSN;
	return (0);
}
