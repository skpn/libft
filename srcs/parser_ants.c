#include "libft.h"
#include "lem_in.h"

int		parse_ants(t_lem *lem, char **line, int *index)
{
	long unsigned	nb_ants;
	int				i;

	PRINTPOSN;
	if (**line == '#')
		return (1);
	nb_ants = 0;
	i = -1;
	while ((*line)[++i] >= '0' && (*line)[i] <= '9')
		nb_ants = nb_ants * 10 + (*line)[i] - '0';
	if ((*line)[i])
		return (0);
	lem->nb_ants = nb_ants;
	(*index)++;
	PRINTPOSN;
	return (1);
}
