/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:05:10 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/08 14:25:50 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char const *s1, char const *s2, int opt)
{
	char	*new;
	int		len;
	int		pos;

	new = NULL;
	if (s1 && s2)
	{
		len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
		if (!(new = (char *)easymalloc(len)))
			return (NULL);
		pos = -1;
		while (s1[++pos])
			new[pos] = s1[pos];
		len = pos--;
		while (s2[++pos - len])
			new[pos] = s2[pos - len];
	}
	else if (s1 || s2)
	{
		if (!(new = ft_strdup(s1 ? (char *)s1 : (char *)s2)))
			return (NULL);
	}
	opt == 3 || opt == 1 ? ft_free((void **)&s1) : 0;
	opt == 3 || opt == 2 ? ft_free((void **)&s2) : 0;
	return (new);
}
