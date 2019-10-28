#include "libft.h"
#include "lem_in.h"
#include <stdlib.h>

#define START 1
#define END 2

int		parse_coord(char *line, int *i)
{
	int		atoi;

	atoi = 0;
	while (line[++(*i)] && line[*i] != ' ')
		atoi = atoi * 10 + (line[*i] - '0');
	if (!line[*i])
		return (0);
	atoi = 0;
	while (line[++(*i)] && line[*i] != ' ')
		atoi = atoi * 10 + (line[*i] - '0');
	if (line[*i])
		return (0);
	return (1);
}

int		manage_start_end(t_lem *lem, char *line, int *start_end)
{
	int		ret;

	if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
	{
		*start_end = ((!ft_strcmp(line, "##start") ? START : END));
		lem->anthill = ft_strjoin_free(lem->anthill, line, 3);
		if ((ret = filler_gnl(0, &line)) <= 0)
			return (0);
	}
	else if (line[0] == '#')
	{
		if ((ret = filler_gnl(0, &line)) <= 0)
			return (0);
	}
	else if (line[0] == 'L')
		return (0);
	return (1);
}

int		parse_room(t_lem *lem, char *line, int *index)
{
	int		i;
	int		start_end;
	t_room	*room;
	t_lst	*lst;
	
	if (ft_strstr(line, "-") && !ft_strstr(line, " ") && (*index)++)
		return (parse_tube(lem, line, index));
	start_end = 0;
	if (!(manage_start_end(lem, line, &start_end)))
		return (0);
	i = -1;
	if (!(room = (t_room *)easymalloc(sizeof(t_room))))
		return (0);
	while (line[++i] && line[i] != ' ')
		;
	if (!(room->name = ft_strsub(line, 0, i)) || !line[i] || !parse_coord(line, &i))
		return (0);
	if (!(lst = ft_lstadd_new(&lem->rooms, room, sizeof(t_room))))
		return (0);
	if (start_end == START)
		lem->start = room;
	else if (start_end == END)
		lem->end = room;
	lem->nb_rooms++;
	return (1);
}
