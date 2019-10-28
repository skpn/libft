/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:03:51 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/24 15:48:43 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclr(t_lst **begin_list)
{
	t_lst *tmp;

	if (!(*begin_list))
		return ;
	while (*begin_list)
	{
		tmp = (*begin_list)->next;
		easyfree((void **)(*begin_list)->content);
		easyfree((void **)begin_list);
		*begin_list = tmp;
	}
}
