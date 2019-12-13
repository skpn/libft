
#include "libft.h"

void	ft_lstswap_contents(t_lst *upstream, t_lst *downstream)
{
	void	*tmp;

	tmp = upstream->content;
	upstream->content = downstream->content;
	downstream->content = tmp;
}
