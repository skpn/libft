/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:56:31 by sikpenou          #+#    #+#             */
/*   Updated: 2019/11/06 15:02:06 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_content(void *content, unsigned opt)
{
	if (opt == CTYPE)
		printf("content: '%c'\n", *(char *)content);
	else if(opt == STYPE)
		printf("content: '%s'\n", (char *)content);
	else if(opt == DTYPE)
		printf("content: %d\n", *(int *)content);
	else if(opt == UTYPE)
		printf("content: %u\n", *(unsigned *)content);
	else if(opt == OTYPE)
		printf("content: %o\n", *(unsigned *)content);
	else if(opt == XTYPE)
		printf("content: %x\n", *(unsigned *)content);
}

void	ft_lstprint(t_head *head, char *name, unsigned opt)
{
	int		i;
	t_lst	*elem;

	i = 0;
	printf("\nprinting list '%s'\n--\nlist start\n--\n", name);
	printf("head: %p, size: %u, first: %p, last: %p\n"
		, head, head->size, head->first, head->last);
	if (!(elem = head->first))
	{
		printf("--\nlist '%s' is empty\n--\n", name);
		return ;
	}
	printf("first->prev: %p - last->next: %p\n--\n"
		, head->first->prev, head->last->next);
	while (elem)
	{
		printf("link %d: %-14p, prev %-14p, content %-14p\n"
			, ++i, elem, elem->prev, elem->content);
		if (opt)
			print_content(elem->content, opt);
		elem = elem->next;
	}
	printf("--\nlist end\n--\n\n");
}
