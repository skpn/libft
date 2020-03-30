/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:33:46 by skpn              #+#    #+#             */
/*   Updated: 2020/03/27 11:19:10 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READ_FILE_H
# define FT_READ_FILE_H

# define READ_FILE_BUF 40000
# define READ_FILE_MAX_SIZE 4000000
# define READ_FILE_FREE_CONTENT 1
# define READ_FILE_FREE_FILE 2
# define READ_FILE_FREE_BOTH 3

typedef struct	s_ft_file
{
	int			fd;
	unsigned	size;
	char		*content;
}				t_file;

void			free_file(t_file *file, int opt);

int				read_file(t_file *file, char *file_name);

#endif