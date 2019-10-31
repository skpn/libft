/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:03:51 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/31 12:32:36 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclr(t_lst **begin_list, int opt)
{
	t_lst *tmp;

	if (!(*begin_list))
		return ;
	while (*begin_list)
	{
		tmp = (*begin_list)->next;
		opt ? easyfree((void **)(*begin_list)->content) : 0;
		easyfree((void **)begin_list);
		*begin_list = tmp;
	}
	*begin_list = NULL;
}
