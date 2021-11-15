#include "libft.h"

t_list	*ft_lsthead_2p(t_list *lst)
{
	if (!lst)
		return(NULL);
	while (lst->prev != NULL)
		lst = lst->prev;
	return(lst);
}
