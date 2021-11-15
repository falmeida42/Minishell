#include "libft.h"

t_list	*ft_lstdup_2p(t_list *lst)
{
	t_list *new;

	new = (t_list*)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->name = lst->name;
	new->content = lst->content;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
