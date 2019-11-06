/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_gnl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 18:42:27 by sikpenou          #+#    #+#             */
/*   Updated: 2019/11/02 10:06:58 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int		get_line(char **buf, unsigned *pos, unsigned *done, char **line)
{
	int		n_pos;

	if ((n_pos = ft_strchr_pos(*buf + *pos, '\n')) == -1)
	{
		if (!(*line = ft_strdup(*buf + *pos)))
			return (-1);
		if (!**buf)
			ft_free((void **)buf);
		if (*done == 1)
		{
			*buf = *line;
			return (1);
		}
		return (0);
	}
	*(*buf + *pos + n_pos) = 0;
	*line = *buf + *pos;
	*pos += n_pos + 1;
	return (1);
}

int		prep_loop(char **buf, int *size, unsigned *done)
{
	if (!(ft_realloc((void **)buf, *size, BUFF_SIZE + 1)))
		return (-1);
	*done = 0;
	(*buf)[BUFF_SIZE] = 0;
	*size += BUFF_SIZE;
	return (1);
}

int		gnl_lem_in(int fd, unsigned *pos, unsigned *done, char **line)
{
	static char		*buf = NULL;
	int				ret;
	int				size;
	
	size = *done == 1 ? ft_strlen(buf) : 0;
	*done == 1 ? (*pos = 0) : 0;
	if (!buf || *done == 1)
	{
		if (prep_loop(&buf, &size, done) < 0)
			return (-1);
		while (size < 500000
			&& (ret = read(fd, buf + *pos, BUFF_SIZE)) == BUFF_SIZE)
		{
			if (ret < 0	|| !(ft_realloc((void **)&buf, size, BUFF_SIZE)))
			{
				buf ? ft_free((void **)&buf) : 0;
				return (-1);
			}
			*pos += BUFF_SIZE;
			(size += BUFF_SIZE) > 500000 ? (*done = 1) : 0;
		}
		buf[*pos + ret] = 0;
		*pos = 0;
	}
	return (get_line(&buf, pos, done, line));
}
