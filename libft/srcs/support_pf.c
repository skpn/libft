/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_pf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 20:27:53 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/02 09:58:07 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int							ft_display(t_buf *buf, int opt)
{
	if (!opt)
	{
		ft_free((void **)buf->str);
		exit(0);
	}
	return (buf->pos);
}

int							add_to_buf(char *str, t_buf *buf)
{
	int		pos;

	pos = 0;
	while (str[pos])
	{
		if (!(buf->pos % BLOCK))
			if (!(buf->size = ft_realloc((void **)&(buf->str), buf->size,
				BLOCK)))
				return (0);
		buf->str[buf->pos++] = str[pos++];
	}
	ft_free((void **)&str);
	return (1);
}

unsigned long long int		ft_ato_ull(const char *str, int *pos)
{
	unsigned long long		nb;

	nb = 0;
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + *str - 48;
		str++;
		(*pos)++;
	}
	(*pos)--;
	return (nb);
}
