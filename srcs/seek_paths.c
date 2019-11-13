
#include "lem_in.h"
#include "libft.h"

t_room	*get_next_room(t_path *current_path, t_lst *room_list)
{
	t_room	*next;
	t_room	*test;

	next = NULL;
	while (room_list)
	{
		test = room_list->content;
		if (!next || next->walk > test->walk || next->dist > test->dist)
			if (test->current_path != current_path)
				next = test;
		room_list = room_list->next;
	}
	return (next);
}

int		try_path(t_lem *lem, t_path *path, t_room *current)
{
	t_room	*next;

	while (1)
	{
		current->walk++;
		current->current_path = path;
		next = get_next_room(path, current->children->first);
		if (next == NULL)
			return (0);
		else if (next->dist == 0)
			return (1);
		if (path->rooms->size == lem->max_dist)
			return (0);
		if (!(ft_lstadd_new(path->rooms, current)))
			return (0);
		current = next;
	}
}

int		seek_paths(t_lem *lem)
{
	t_path	*test_path;
	t_room	*start_room;

	if (!(test_path = new_path()))
		return (0);
	while (lem->config->nb_paths < lem->max_paths)
	{
		start_room = get_next_room(NULL, lem->start->children->first);
		if (!start_room)
			return (0);
		if (try_path(lem, test_path, start_room) == 1)
		{
			if (update_config(lem, lem->config, test_path) == 0)
				return (0);
			if (!(test_path = new_path()))
				return (0);
		}
		else
		{
			ft_lstfree(&test_path->rooms, FREE_LINKS, KEEP_HEAD);
		}
	}
	return (1);
}
