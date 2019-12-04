/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_words_tables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 15:04:33 by sikpenou          #+#    #+#             */
/*   Updated: 2019/04/05 11:02:27 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_words_tables(char **tab)
{
	int		word;

	word = 0;
	if (!tab || !*tab)
		return ;
	while (tab[word])
	{
		ft_putstr(tab[word]);
		ft_putchar('\n');
		word++;
	}
}
