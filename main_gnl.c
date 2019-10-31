/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 19:33:23 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/31 19:48:54 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
//#include "/Users/sikpenou/my_libft/includes/libft.h"

int		gnl_lem_in(int fd, int *pos, char **line);

int		main(int ac, char **av)
{
	if(!ac || !av)
		return(0);
	int		fd = open(av[1], O_RDONLY);
	int		pos;
	char	*line;
	int		ret;

	pos = 0;
	while ((ret = gnl_lem_in(fd, &pos, &line) == 1))
		printf("%s\n", line);
	printf("final ret: %d\n", ret);
}
