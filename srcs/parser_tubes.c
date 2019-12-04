#include "libft.h"
#include "lem_in.h"

int		add_links(t_lem *lem, char *name1, char *name2)
{
	t_lst	*elem;
	t_room	*room;
	t_room	*room1;
	t_room	*room2;
	int		ctr;

	elem = lem->rooms->first;
	ctr = 0;
	while (elem && ctr < 2)
	{
		room = (t_room *)elem->content;	
		if (!ft_strcmp(room->name, name1) && ++ctr)
			room1 = room;
		else if (!ft_strcmp(room->name, name2) && ++ctr)
			room2 = room;
		elem = elem->next;
	}
	if (ctr != 2)
		return (0);
	if (ft_lstfind(room1->children, room2))
		return (1);
	printf("adding:\n");
	print_room(room1);
	print_room(room2);
	dprintf(g_fd, "adding child to room1\n");
	ft_lstadd_new(room1->children, room2);
	dprintf(g_fd, "adding child to room2\n");
	ft_lstadd_new(room2->children, room1);
	return (1);
}

int		parse_tube(t_lem *lem, char **line, int *index)
{
	int		pos1;
	int		pos2;
	char	*name1;
	char	*name2;

	(void)index;
	printf("in parser tube with line: '%s'\n", *line);
	if (**line == '#')
		return ((*line)[1] == '#' ? 0 : 1);
	if ((pos1 = ft_strchr_pos(*line, '-')) < 1 || !(name1 = ft_strsub(*line, 0,
		pos1)))
		return (0);
	if ((pos2 = ft_strlen(*line)) < 3
		|| !(name2 = ft_strsub(*line, pos1 + 1, pos2 - pos1 - 1)))
		return (0);
	if ((ft_strchr_pos(name2, '-')) > -1)
		return (0);
	if (!add_links(lem, name1, name2))
		return (0);
	ft_free((void **)&name1);
	ft_free((void **)&name2);
	return (1);
}
