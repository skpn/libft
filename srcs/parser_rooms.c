
#include "libft.h"
#include "lem_in.h"
#include <stdlib.h>

#define START 1
#define END 2

int		parse_coord(char *line)
{
	int		atoi;

	atoi = 0;
	while (*(++line) && *line != ' ')
		atoi = atoi * 10 + *line - '0';
	if (!*line)
		return (0);
	atoi = 0;
	while (*(++line) && *line != ' ')
		atoi = atoi * 10 + *line - '0';
	if (*line)
		return (0);
	return (1);
}

int		manage_start_end(t_lem *lem, char **line, int *start_end)
{
	int		ret;

	if (!ft_strcmp(*line, "##start") || !ft_strcmp(*line, "##end"))
	{
		*start_end = ((!ft_strcmp(*line, "##start") ? START : END));
		lem->anthill = ft_strjoin_anthill(&(lem->anthill), line, LEFT);
		if ((ret = gnl_lem_in(0, &(lem->shortest), &(lem->max_dist), line))
			<= 0)
			return (0);
	}
	else if (**line == '#')
	{
		if ((ret = gnl_lem_in(0, &(lem->shortest), &(lem->max_dist), line))
			<= 0)
			return (0);
	}
	else if (**line == 'L')
		return (0);
	return (1);
}

int		parse_room(t_lem *lem, char **line, int *index)
{
	int		i;
	int		start_end;
	t_room	*room;

	if (ft_strchr_pos(*line, '-') > -1 && ft_strchr_pos(*line, ' ') == -1
		&& (*index)++)
		return (parse_tube(lem, line, index));
	start_end = 0;
	if (!(manage_start_end(lem, line, &start_end))
		|| !(room = new_room()))
		return (0);
	i = 0;
	while ((*line)[i] && (*line)[i] != ' ')
		i++;
	if (!(*line)[i])
		return (0);
	(*line)[i] = 0;
	dprintf(g_fd, "line dup for room name\n");
	if (!(room->name = ft_strdup(*line)) || !parse_coord(*line + i))
		return (0);
	dprintf(g_fd, "new list elem for room\n");
	if (!(ft_lstadd_new(lem->rooms, room)))
		return (0);
	if (start_end)
		start_end == START ? (lem->start = room) : (lem->end = room);
	lem->nb_rooms++;
	return (1);
}
