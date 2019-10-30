/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 12:40:21 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/30 17:29:27 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst		*ft_lstadd_new(t_lst **alst, void *content, int size)
{
	t_lst	*new;

	(void)size;
	if (!(new = ft_lstnew(NULL, 0)))
		return (NULL);
	new->content = content;
	if (alst)
		ft_lstadd(alst, new);
	return (new);
}
