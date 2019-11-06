/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testpop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 15:23:24 by sikpenou          #+#    #+#             */
/*   Updated: 2019/11/02 16:11:36 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		main(int ac, char **av)
{
	t_lst	*lst1;
	t_lst	*lst2;
	t_lst	*lst3;
	t_lst	*ret;

	(void)ac;
	(void)av;
	lst1 = ft_lstnew("1");
	lst2 = ft_lstnew("2");
	lst3 = ft_lstnew("3");
	ft_lstadd(&lst1, lst2);
	ft_lstadd(&lst1, lst3);
	ft_lstprint(lst1, ADDR, 2);
	printf("popping %p\n", lst2);
	ret = ft_lstpop(&lst1, lst2);
	printf("ret: %p\n", ret);
	ft_lstprint(lst1, ADDR, 2);
	return (0);
}
