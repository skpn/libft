/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:56:29 by sikpenou          #+#    #+#             */
/*   Updated: 2020/03/27 11:21:42 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

/*
** This file reader takes a t_file pointer and a file name and fills the t_file
** structure with the correct fd, file size, and file content (malloc'ed)
**
** The free function takes an option to free the t_file as well in case it was
** malloc'ed
**
** The reading buffer size and max file size are defined in ft_read_file.h
*/

void		free_file(t_file *file, int opt)
{
	if (file->content)
		easyfree((void **)&file->content);
	if (opt == FREE_STRUCT)
		easyfree((void **)&file);
}

static int	read_loop(t_file *file)
{
	int		ret;

	while ((ret = read(file->fd, file->content + file->size
		, READ_FILE_BUF)) >= 0 && file->size < READ_FILE_MAX_SIZE)
	{
		file->size += ret;
		if (ret == READ_FILE_BUF && ft_realloc(&file->content, file->size
			, READ_FILE_BUF) != EXIT_SUCCESS)
		{
			easyfree((void **)&file->content);
			return (ERROR_MALLOC);
		}
		else
		{
			file->content[file->size] = '\0';
			return (EXIT_SUCCESS);
		}
	}
	easyfree((void **)&file->content);
	return (ret < 0 ? ERROR_READ : ERROR_FILE_TOO_LARGE);
}

int			read_file(t_file *file, char *file_name)
{
	int		ret;

	if ((file->fd = open(file_name, O_RDONLY)) < 3)
		return (ERROR_OPEN_FD);
	if (!(file->content = (char *)malloc(READ_FILE_BUF + 1)))
		return (ERROR_MALLOC);
	file->content[READ_FILE_BUF] = 0;
	file->size = 0;
	ret = read_loop(file);
	close(file->fd);
	return (ret);
}
