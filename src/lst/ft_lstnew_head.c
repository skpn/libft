/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsthead_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 11:28:08 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/18 18:36:49 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_head	*ft_lstnew_head(void)
{
	t_head	*head;

	if (!(head = (t_head *)easymalloc(sizeof(*head))))
		return (0);
	return (head);
}
