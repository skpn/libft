/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 12:40:21 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/24 14:21:52 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst		*ft_lstadd_new(t_lst **alst, void *content, int size)
{
	t_lst	*new;

	if (!(new = ft_lstnew(content, size)))
		return (NULL);
	if (alst)
		ft_lstadd(alst, new);
	return (new);
}
