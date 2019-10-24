/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 00:23:34 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/08 14:24:18 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

int		ft_printf(const char *str, ...)
{
	va_list		arg_list;
	t_buf		buf;
	int			ret;

	get_gc_list(1);
	if (!str)
		return (0);
	ft_init(&buf, NULL, 1);
	va_start(arg_list, str);
	base_func(&buf, str, arg_list);
	write(1, buf.str, buf.pos);
	if (buf.str)
		ft_free((void **)buf.str);
	ret = buf.pos;
	return (ret);
}

int		ft_fprintf(int fd, const char *str, ...)
{
	va_list		arg_list;
	t_buf		buf;
	int			ret;

	get_gc_list(1);
	if (!str)
		return (0);
	ft_init(&buf, NULL, 1);
	va_start(arg_list, str);
	base_func(&buf, str, arg_list);
	write(fd, buf.str, buf.pos);
	if (buf.str)
		ft_free((void **)buf.str);
	ret = buf.pos;
	return (ret);
}

int		ft_sprintf(char **res, const char *str, ...)
{
	va_list					arg_list;
	t_buf					buf;

	get_gc_list(1);
	if (!str || !res)
		return (0);
	ft_init(&buf, NULL, 1);
	va_start(arg_list, str);
	base_func(&buf, str, arg_list);
	*res = buf.str;
	return (buf.pos);
}
