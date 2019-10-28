/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:01:47 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/24 15:44:58 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include <unistd.h>
# include "libft.h"

typedef struct		s_room
{
	long			dist;
	long			lvl;
	char			*name;
	t_lst			*parents;
	t_lst			*children;
}					t_room;

typedef struct 		s_lem
{
	long unsigned	nb_ants;
	long unsigned	nb_rooms;
	char			*anthill;
	t_lst			*rooms;
	t_room			*start;
	t_room			*end;
	t_lst			*paths;
}					t_lem;

int					parse_ants(t_lem *lem, char *line, int *index);
int					parse_room(t_lem *lem, char *line, int *index);
int					parse_tube(t_lem *lem, char *line, int *index);

void				print_anthill(t_lem *lem);
void				print_lem(t_lem *lem, char *args);
void				free_room(t_room **room);
int					exit_lem(t_lem *lem, char *msg, int ret);
int					parse_input(t_lem *lem);

#endif
