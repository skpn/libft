
#include "libft.h"
#include "lem_in.h"

void	calculate_turns(t_lst *path_elem, unsigned ants, unsigned shortest
	, t_config *config)
{
	t_path		*current_path;

	config->turns = 0;
	while (path_elem)
	{
		current_path = path_elem->content;
		added_turns = (ants - current_path->rooms->size + shortest) / nb_paths;
		ants -= nb_paths * added_turns;
		config->turns += added_turns;
		current_path->turns = turns;
		nb_paths--;
		path_elem = path_elem->next;
	}
}

void	balance_load(t_lem *lem, t_config *new_config)
{
	unsigned	ants;
	unsigned	added_turns;
	unsigned	shortest;
	t_head		*new_paths;

	new_paths = new_config->paths;
	ants = lem->nb_ants;
	nb_paths = new_paths->size;
	shortest = new_paths->last->content->rooms->size;
	calculate_turns(new_paths->first, ants, shortest, config);
}
