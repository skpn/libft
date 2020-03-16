/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:56:29 by sikpenou          #+#    #+#             */
/*   Updated: 2020/03/03 14:50:38 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

void		free_file(t_file *file)
{
	if (file->content)
		easyfree((void **)&file->content);
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
			free_file(file);
			return (ERROR_MALLOC);
		}
		else
		{
			file->content[file->size] = '\0';
			return (EXIT_SUCCESS);
		}
	}
	free_file(file);
	return (ret < 0 ? ERROR_READ : ERROR_FILE_TOO_LARGE);
}

int			read_file(t_file *file, char *file_name)
{
	int		ret;

	file->fd = open(file_name, O_RDONLY);
	if (file->fd < 3)
		return (ERROR_OPEN_FD);
	if (!(file->content = (char *)malloc(READ_FILE_BUF + 1)))
		return (ERROR_MALLOC);
	file->content[READ_FILE_BUF] = 0;
	file->size = 0;
	if ((ret = read_loop(file)) != EXIT_SUCCESS)
		return (ret);
	close(file->fd);
	return (EXIT_SUCCESS);
}
