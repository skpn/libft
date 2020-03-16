/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:16:51 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/27 18:30:31 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

int		parse_pf_arg(t_pf *pf)
{
	char		c;
	t_pf_arg	*arg;

	arg = &pf->arg;
	arg->field = FIELD_D;
	while ((c = pf->format[pf->format_pos++]) != 0)
	{
		if (ft_ischarset(c, PF_FLAGS))
			parse_pf_arg_flag(pf, arg, c);
		else if (c == '.' || c == '*' || ft_ischarset(c, "123456789"))
		{
			parse_pf_arg_size(pf, arg, &arg->width, c);
		}
		else if (c == 'h' || c == 'l')
			parse_pf_arg_field(pf, arg, c);
		else if (ft_ischarset(c, PF_TYPES))
			return (parse_pf_arg_type(pf, arg, c));
		else
		{
			return (ERROR_BAD_TYPE);
		}
	}
	return (ERROR_NO_TYPE);
}

int		expand_pf_format(t_pf *pf)
{
	char	c;
	int		check_ret;

	while ((c = pf->format[pf->format_pos++]) != 0)
	{
		if (c == '%')
		{
			ft_memset(&pf->arg, 0, sizeof(pf->arg));
			if ((c = pf->format[pf->format_pos]) != '%' && c != 0
				&& (check_ret = parse_pf_arg(pf)) != EXIT_SUCCESS)
				return (check_ret);
		}
		else
		{
			pf->str[pf->pos++] = c;
			if (pf->pos == PF_BUF_SIZE)
			{
				if (ft_realloc(&pf->str, pf->size, PF_BUF_SIZE) != EXIT_SUCCESS)
					return (ERROR_MALLOC);
				pf->size += PF_BUF_SIZE;
			}
		}
	}
	pf->str[pf->pos] = 0;
	return (EXIT_SUCCESS);
}

void	init_pf_func_tab(t_pf *pf)
{
	pf->func[TYPE_C] = &expand_type_c;
	pf->func[TYPE_S] = &expand_type_s;
	pf->func[TYPE_P] = &expand_type_unsigned;
	pf->func[TYPE_D] = &expand_type_signed;
	pf->func[TYPE_U] = &expand_type_unsigned;
	pf->func[TYPE_X] = &expand_type_unsigned;
}

int		core_pf_2(t_pf *pf)
{
	int			check_ret;
	t_func_pf	func[NB_PF_TYPES];

	if (PF_BUF_SIZE < 1 || PF_BUF_SIZE % 8)
		return (EXIT_FAILURE);
	pf->func = func;
	init_pf_func_tab(pf);
	if (!(pf->str = (char *)malloc(PF_BUF_SIZE)))
		return (ERROR_MALLOC);
	pf->size = PF_BUF_SIZE;
	if ((check_ret = expand_pf_format(pf)) != EXIT_SUCCESS)
		return (check_ret);
	return (EXIT_SUCCESS);
}
