/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_gnl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 18:42:27 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/31 19:45:01 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int		get_line(char *buf, int *pos, char **line)
{
	int		n_pos;
	int		ret;

	if ((n_pos = ft_strchr_pos(buf + *pos, '\n')) == -1)
		ret = 0;
	if (ret == 0)
	{
		if (!(*line = ft_strdup(buf + *pos)))
			return (-1);
		ft_free((void **)&buf);
		return (0);
	}
	*(buf + *pos + n_pos) = 0;
	*line = buf + *pos;
	*pos += n_pos + 1;
	return (1);
}

int		gnl_lem_in(int fd, int *pos, char **line)
{
	static char		*buf = NULL;
	int				ret;
	int				size;

	if (!buf)
	{
		if (!(buf = (char *)easymalloc(40001)))
			return (-1);
		buf[40000] = 0;
		size = 40001;
		while ((ret = read(fd, buf + *pos, 40000)) == 40000)
		{
			if (ret < 0 || size > 500000
				|| !(ft_realloc((void **)&buf, size, 40000)))
				return (-1);
			size += 40000;
			*pos += 40000;
		}
		buf[*pos + ret] = 0;
		*pos = 0;
	}
	return (get_line(buf, pos, line));
}
