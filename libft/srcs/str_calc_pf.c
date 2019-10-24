/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_calc_pf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 11:50:33 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/21 12:50:33 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	prep_len(char **sht, char **lng, int *l_sht, int *l_lng)
{
	int		tmp;

	*l_sht = ft_strlen(*sht);
	*l_lng = ft_strlen(*lng);
	if (*l_lng < *l_sht)
	{
		ft_swapstr(lng, sht);
		tmp = *l_sht;
		*l_sht = *l_lng;
		*l_lng = tmp;
	}
}

char	*ft_strmult(char *nb, char *mul)
{
	char	*ret;
	int		l_nb;
	int		l_mul;
	int		off;
	int		pos;

	prep_len(&nb, &mul, &l_nb, &l_mul);
	if (!(ret = (char *)easymalloc(l_mul + l_nb + 1)))
		return (0);
	off = 0;
	while (off++ < l_nb && (pos = l_mul))
	{
		while (pos--)
		{
			ret[l_nb + pos - off + 1] += (nb[l_nb - off] - 48) * (mul[pos]
				- 48);
			ret[l_nb + pos - off] += ret[l_nb + pos - off + 1] / 10;
			ret[l_nb + pos - off + 1] = ret[l_nb + pos - off + 1] % 10;
		}
	}
	while (++pos < l_mul + l_nb)
		ret[pos] += 48;
	return (ret);
}

char	*ft_strdiv(char **nb, int turns, int len, int pos)
{
	char	*ret;
	int		keep;
	int		carry;

	len = ft_strlen(*nb) + turns;
	if (!(ret = (char *)easymalloc(len + 1)))
		ft_display(NULL, 0);
	while (++pos < len - turns)
		ret[pos] = (*nb)[pos] - 48;
	while ((pos = -1) && turns--)
	{
		carry = 0;
		while (++pos < len)
		{
			keep = ret[pos];
			ret[pos] = (ret[pos] >> 1) + carry;
			carry = (keep & 1) + ((keep & 1) << 2);
		}
	}
	while (++pos < len)
		ret[pos] += 48;
	while (ret[--pos] == '0')
		ret[pos] = 0;
	ft_free((void **)nb);
	return (ret);
}

char	*ft_stradd_fract(char *sht, char *lng)
{
	int		l_sht;
	int		l_lng;
	char	*ret;

	prep_len(&sht, &lng, &l_sht, &l_lng);
	if (!(ret = ft_strdup(lng)))
		return (0);
	while (l_sht-- > 1)
	{
		ret[l_sht] += sht[l_sht] - 48;
		ret[l_sht - 1] += (ret[l_sht] - 48) / 10;
		ret[l_sht] = (ret[l_sht] - 48) % 10 + 48;
	}
	return (ret);
}

char	*ft_stradd(char *sht, char *lng)
{
	int		pos;
	int		len;
	char	*ret;

	prep_len(&sht, &lng, &len, &pos);
	if (!(ret = (char *)easymalloc(pos + 2)))
		return (0);
	ft_memset(ret, '0', pos + 1);
	ret[pos + 1] = 0;
	while (--len > -1 && --pos > -1)
	{
		ret[pos] = (lng[pos] + sht[len] + ret[pos + 1] - (48 << 1) - 48) / 10
			+ 48;
		ret[pos + 1] = (lng[pos] + sht[len] + ret[pos + 1] - (48 >> 1) - 48)
			% 10 + 48;
	}
	while (pos-- > 0)
	{
		ret[pos] = (lng[pos] + ret[pos + 1] - (48 << 1)) / 10 + 48;
		ret[pos + 1] = (lng[pos] + ret[pos + 1] - (48 << 1)) % 10 + 48;
	}
	return (ret);
}
