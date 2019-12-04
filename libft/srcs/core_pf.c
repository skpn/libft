/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_pf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 20:26:52 by sikpenou          #+#    #+#             */
/*   Updated: 2019/11/03 20:08:54 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_arg		*ft_init(t_buf *buf, t_arg *arg, int opt)
{
	if (opt)
	{
		ft_memset(buf, 0, sizeof(*buf));
		buf->tab[0] = &f_percent;
		buf->tab[1] = &f_c;
		buf->tab[2] = &f_s;
		buf->tab[3] = &f_p;
		buf->tab[4] = &f_num_s;
		buf->tab[5] = &f_num_u;
	}
	else
	{
		ft_memset(arg, 0, sizeof(*arg));
		arg->prefix = "";
	}
	return (arg);
}

int			get_field(t_arg *arg, const char *str, int pos, int check)
{
	if ((check = ft_strchr_pos(FIELD, str[pos])) > -1)
	{
		if ((str[pos] == 'h' || str[pos] == 'l') && str[pos + 1] == str[pos])
		{
			check++;
			pos++;
		}
		arg->field = check + 1;
	}
	return (pos);
}

int			get_size(va_list arg_list, const char *str, int *pos
	, unsigned long *prec)
{
	unsigned long long int		ret;

	if (str[*pos] == '*')
	{
		ret = (int)va_arg(arg_list, int);
	}
	else
	{
		ret = ft_ato_ull(str, pos);
	}
	if (prec)
		*prec = 1;
	if (ret > 2000000)
		ft_display(NULL, 0);
	else if ((int)ret < 0)
		ret = 0;
	return (ret);
}

int			ft_parse(t_arg *arg, const char *str, t_buf *buf, va_list arg_list)
{
	int		pos;
	int		check;

	pos = -1;
	while (str[++pos] && ft_strchr_pos(ALL, str[pos]) > -1)
	{
		if ((check = ft_strchr_pos(FLAGS, str[pos])) > -1)
			arg->flags |= (1 << check);
		else if (ft_isdigit(str[pos]) || (str[pos] == '*' && ++pos))
			arg->min = get_size(arg_list, str + pos, &pos, 0);
		else if ((str[pos] == '.' || str[pos] == '*') && ++pos)
			arg->max = get_size(arg_list, str + pos, &pos, &arg->prec);
		else if ((check = ft_strchr_pos(FIELD, str[pos])) > -1)
			pos = get_field(arg, str, pos, check);
	}
	check = str[pos] == 'i' ? (int)DTYPE : ft_strchr_pos(TYPE, str[pos]);
	if (check < 0)
		return (ft_display(buf, 0));
	arg->type = check;
	arg->start = buf->pos;
	if (arg->type > DTYPE)
		buf->tab[DTYPE + 1](arg, buf, arg_list);
	else
		buf->tab[arg->type](arg, buf, arg_list);
	return (pos + 1);
}

int			base_func(t_buf *buf, const char *str, va_list arg_list)
{
	t_arg			arg;
	unsigned int	str_pos;

	str_pos = 0;
	while (str[str_pos])
	{
		if (buf->pos == buf->size)
			if (!(buf->size = ft_realloc((void *)&(buf->str), buf->size
						, BLOCK)))
				return (ft_display(buf, 0));
		if (str[str_pos] == '%')
		{
			str_pos += ft_parse(ft_init(buf, &arg, 0), str + str_pos + 1, buf
				, arg_list) + 1;
		}
		else
		{
			buf->str[buf->pos++] = str[str_pos++];
		}
	}
	if (buf->str)
		buf->str[buf->pos] = 0;
	return (0);
}
