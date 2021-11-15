#include "libft.h"

t_env	*ft_envhead_2p(t_env *lst)
{
	if (!lst)
		return(NULL);
	while (lst->prev != NULL)
		lst = lst->prev;
	return(lst);
}
