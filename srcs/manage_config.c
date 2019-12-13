
#include "libft.h"
#include "lem_in.h"

t_config	*copy_config(t_config *original)
{
	t_config	*new_config;
	t_head		*new_head;

	if (!(new_config = alloc_new_config()))
		return (NULL);
	if (!(new_head = ft_lstcpy(original->paths)))
		return (NULL);
	new_config->paths = new_head;
	new_config->turns = original->turns;
	return (new_config);
}

int			get_max_walk(t_lem *lem)
{
	unsigned	walk;
	t_lst		*parent;

	walk = 0;
	parent = lem->end->parents->first;
	while (parent)
	{
		if (((t_room *)parent->content)->walk > walk)
			walk = ((t_room *)parent->content)->walk;
		parent = parent->next;
	}
	printf("walk = %u, lem->walk_limit = %u\n", walk, lem->walk_limit);
	return (walk);
}

int		replace_config(t_head *config_lst, t_config *current_config,
	t_config *old_config)
{
	t_config	*copy;
	t_lst		*old_config_elem;

	if (!(copy = copy_config(current_config)))
		return (0);
	old_config_elem = ft_lstfind(config_lst, old_config);
	old_config_elem->content = current_config;
	free_config(&old_config);
	return (1);
}

int		compare_configs(t_head *config_lst, t_config *current_config)
{
	t_lst		*elem;
	t_config	*config;

	elem = config_lst->first;
	while (elem)
	{
		config = (t_config *)elem->content;
		if (config->paths->size == current_config->paths->size)
		{
			if (current_config->turns < config->turns)
			{
				if (!(replace_config(config_lst, current_config, config)))
					return (0);
				return (1);
			}
		}
		elem = elem->next;
	}
	return (0);
}

int			add_new_config(t_lem *lem, t_config *current_config)
{
	t_config	*copy;

	if (!(copy = copy_config(current_config)))
		return (0);
	if (!(ft_lstadd_new(lem->config_lst, copy)))
		return (0);
	return (1);
}

int			sorted_cmp(t_lst *ref, t_lst *insert)
{
	unsigned	ref_len;
	unsigned	insert_len;

	ref_len = ((t_path *)ref->content)->rooms->size;
	insert_len = ((t_path *)insert->content)->rooms->size;
	return (ref_len < insert_len);
}

int			manage_valid_path(t_lem *lem, t_path *path)
{
	unsigned	current_nb_paths;
	unsigned	most_paths;
	unsigned	check_alloc;
	t_lst		*new_elem;

	PRINTPOSN;
	print_path(path);
	if (!ft_lstadd_new(lem->paths, path))
		return (0);
	if (!(new_elem = ft_lstnew_elem(path)))
		return (0);
	ft_lstadd_sorted(lem->current_config->paths, new_elem, &sorted_cmp);
	current_nb_paths = lem->current_config->paths->size;
	most_paths = ((t_config *)lem->config_lst->first->content)->paths->size;
	if (current_nb_paths > most_paths)
		check_alloc = add_new_config(lem, lem->current_config);
	else
		check_alloc = compare_configs(lem->config_lst, lem->current_config);
	return (check_alloc);
}
