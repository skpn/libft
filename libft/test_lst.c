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

int		main(int ac, char **av)
{
	if(!ac || !av)
		return(0);
	t_head	*head_a;
	t_head	*head_b;
	t_lst	*elem_a_1;
	t_lst	*elem_a_2;
	t_lst	*elem_a_3;

	head_a = ft_lstnew_head(NULL, NULL);
	head_b = ft_lstnew_head(NULL, NULL);
	elem_a_1 = ft_lstnew_elem(NULL);
	elem_a_2 = ft_lstnew_elem(NULL);
	elem_a_3 = ft_lstnew_elem(NULL);
	ft_lstadd(head_a, elem_a_1);
	ft_lstadd(head_a, elem_a_2);
	ft_lstadd(head_a, elem_a_3);
	elem_a_1->content = ft_strdup(av[1]);
	elem_a_2->content = ft_strdup(av[2]);
	elem_a_3->content = ft_strdup(av[3]);
	ft_lstprint(head_a, "head_a", STYPE);
	ft_lstprint(head_b, "head_b", STYPE);
	ft_lstjoin(head_a, head_b);
	ft_lstprint(head_b, "head_b", STYPE);
	ft_lstfree(&head_b, BOTH, BOTH);
}

//__attribute__((destructor))void gdfgdfg(){while (1) ;}
