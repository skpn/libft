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
#include <stdlib.h>

char	*ft_strjoin_free(char const *s1, char const *s2, int opt)
{
	int		len1;
	int		len2;
	char	*new;

	new = NULL;
	if (s1 && s2)
	{
		len1 = ft_strlen((char *)s1);
		len2 = ft_strlen((char *)s2);
		if (!(new = (char *)malloc(len1 + len2 + 1)))
			return (NULL);
		ft_strcpy(new, (char *)s1);
		ft_strcpy(new + len1, (char *)s2);
	}
	else if (s1 || s2)
		return (ft_strdup(s1 ? s1 : s2));
	opt == 3 || opt == 1 ? ft_free((void **)&s1) : 0;
	opt == 3 || opt == 2 ? ft_free((void **)&s2) : 0;	
	return (new);
}
