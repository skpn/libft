/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 18:44:02 by sikpenou          #+#    #+#             */
/*   Updated: 2019/11/03 21:05:10 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include "libft.h"

int		ft_cmp(t_lst *a, t_lst *b)
{
	if (ft_strcmp((char *)a->content, (char *)b->content) < 0)
		return (0);
	return (1);
}

int		main(int ac, char **av)
{
	if(!ac || !av)
		return(0);
	t_head	*head_a;
//	t_head	*head_b;
	t_lst	*elem_a_1;
//	t_lst	*elem_a_2;
//	t_lst	*elem_a_3;
	int		pos;

	head_a = ft_lstnew_head(NULL, NULL);
//	head_b = ft_lstnew_head(NULL, NULL);
	pos = 0;
	while (av[++pos])
	{
		elem_a_1 = ft_lstnew_elem(ft_strdup(av[pos]));
		ft_lstadd_sorted(head_a, elem_a_1, &ft_cmp);
	}
	ft_lstprint(head_a, "head_a", STYPE);
	ft_lstfree(&head_a, BOTH, BOTH);
}

//__attribute__((destructor))void gdfgdfg(){while (1) ;}
