/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:55:14 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/04 11:00:07 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_free_error_tab(t_error_tab *tab)
{
	unsigned	error_nb;

	error_nb = 0;
	while (error_nb < MAX_ERROR)
	{
		if (tab->error[error_nb] != NULL)
			write(tab->fd, tab->error[error_nb],
				ft_strlen(tab->error[error_nb]));
		++error_nb;
	}
	gc_free((void **)&tab);
}

int		set_error(t_error_tab *tab, unsigned error_nb, char *msg)
{
	char	*error;

	error = NULL;
	if (error_nb >= MAX_ERROR)
		error = "Error tab full\n";
	if (error_nb == EXIT_SUCCESS)
		error = "Error number is EXIT_SUCCESS\n";
	if (tab->error[error_nb] != NULL)
		error = "Error number unavailable\n";
	if (!(tab->error[error_nb] = ft_strdup(msg)))
		error = "Error malloc\n";
	if (!error)
		return (EXIT_SUCCESS);
	write(tab->fd, error, ft_strlen(error));
	return (EXIT_FAILURE);
}

int		ft_set_error_tab(t_error_tab **target_tab, unsigned fd)
{
	t_error_tab	*tab;

	if (!(tab = (t_error_tab *)gc_malloc(sizeof(*tab))))
	{
		write(tab->fd, "Malloc error\n", 13);
		return (EXIT_FAILURE);
	}
	ft_memset(tab, 0, sizeof(*tab));
	tab->fd = fd;
	if (set_error(tab, ERROR_MALLOC, "Malloc error\n") == EXIT_FAILURE
		|| set_error(tab, ERROR_OPEN_FD, "Unable to open file\n")
			== EXIT_FAILURE
		|| set_error(tab, ERROR_READ, "Unable to read\n") == EXIT_FAILURE
		|| set_error(tab, ERROR_D_ARRAY_SIZE, "Error with d_array\n")
			== EXIT_FAILURE
		|| set_error(tab, ERROR_MAGIC_FILE, "Magic file error\n")
			== EXIT_FAILURE
		|| set_error(tab, ERROR_WITHOUT_MSG, "") == EXIT_FAILURE
		|| set_error(tab, ERROR_ERROR_TAB_FULL, "Error tab full\n")
			== EXIT_FAILURE
		|| set_error(tab, ERROR_ERROR_NUMBER_IS_EXIT_SUCCESS,
			"Error number_is_exit_success") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*target_tab = tab;
	return (EXIT_SUCCESS);
}

int		set_stack_error(t_error_tab *tab, unsigned error_nb, char *msg)
{
	char	*error;

	error = NULL;
	if (error_nb >= MAX_ERROR)
		error = "Error tab full\n";
	if (error_nb == EXIT_SUCCESS)
		error = "Error number is EXIT_SUCCESS\n";
	if (tab->error[error_nb] != NULL)
		error = "Error number unavailable\n";
	tab->error[error_nb] = msg;
	if (!error)
		return (EXIT_SUCCESS);
	write(tab->fd, error, ft_strlen(error));
	return (EXIT_FAILURE);
}

void	set_stack_errors_lol(t_error_tab *tab)
{
	set_stack_error(tab, ERROR_MALLOC, "Malloc_error\n");
	set_stack_error(tab, ERROR_OPEN_FD, "Unable to open file lol yystack\n");
	set_stack_error(tab, ERROR_READ, "Unable to read\n");
	set_stack_error(tab, ERROR_D_ARRAY_SIZE, "Error with d_array\n");
	set_stack_error(tab, ERROR_MAGIC_FILE, "Error with magic file\n");
	set_stack_error(tab, ERROR_WITHOUT_MSG, "");
}
