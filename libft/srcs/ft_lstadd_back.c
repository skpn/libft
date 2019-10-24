/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 16:28:56 by sikpenou          #+#    #+#             */
/*   Updated: 2019/08/03 13:23:01 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_lst **alst, t_lst *new)
{
	if (*alst)
	{
		(*alst)->last->next = new;
		(*alst)->last->last = new;
		(*alst)->last = new;
	}
	else
	{
		*alst = new;
		(*alst)->next = NULL;
		(*alst)->last = new;
	}
}
