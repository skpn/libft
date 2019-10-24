/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_funcs_pf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 20:28:19 by sikpenou          #+#    #+#             */
/*   Updated: 2019/09/30 22:21:41 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		f_s(t_arg *arg, t_buf *buf, va_list arg_list)
{
	char		*str;
	unsigned	len;

	len = 0;
	if (!(str = (char *)va_arg(arg_list, char *)))
		str = "(null)";
	while (str[len] && (arg->max ? len < arg->max : 1))
	{
		if (!(buf->pos % BLOCK))
			if (!(buf->size = ft_realloc((void *)&(buf->str), buf->size
						, BLOCK)))
				return (ft_display(buf, 0));
		buf->str[buf->pos] = str[len];
		buf->pos++;
		len++;
	}
	ft_pad(arg, buf);
	return (0);
}

int		f_c(t_arg *arg, t_buf *buf, va_list arg_list)
{
	char	c;

	c = (char)va_arg(arg_list, int);
	if (!(buf->pos % BLOCK))
		if (!(buf->size = ft_realloc((void *)&(buf->str), buf->size
					, BLOCK + 1)))
			return (ft_display(buf, 0));
	buf->str[buf->pos++] = c;
	ft_pad(arg, buf);
	return (0);
}

int		f_percent(t_arg *arg, t_buf *buf, va_list arg_list)
{
	(void)arg_list;
	arg->flags & PLUS ? (arg->flags ^= PLUS) : 0;
	arg->flags & SPACE ? (arg->flags ^= SPACE) : 0;
	if (!(buf->pos % BLOCK))
		if (!(buf->size = ft_realloc((void *)&(buf->str), buf->size, BLOCK)))
			return (ft_display(buf, 0));
	buf->str[buf->pos++] = '%';
	ft_pad(arg, buf);
	return (0);
}

int		f_p(t_arg *arg, t_buf *buf, va_list arg_list)
{
	long long int	addr;
	char			*nil;

	if (arg->max || arg->field || arg->flags & ~MINUS)
		return (ft_display(buf, 0));
	if (!(addr = (unsigned long long int)va_arg(arg_list, long int)))
	{
		nil = "0x0";
		if (buf->pos + 3 > buf->size
			&& !(buf->size = ft_realloc((void *)&(buf->str), buf->size, BLOCK)))
			return (ft_display(buf, 0));
		while (*nil)
			buf->str[buf->pos++] = *(nil++);
	}
	else
	{
		arg->prefix = "0x";
		buf->pos = ft_itoa_base_u(addr, "0123456789abcdef", buf, arg);
	}
	return (ft_pad(arg, buf));
}
