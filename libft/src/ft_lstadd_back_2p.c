#include "libft.h"

void	ft_lstadd_back_2p(t_list **lst, t_list *new)
{
	t_list *temp;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		temp = ft_lstlast(*lst);
		temp->next = new;
		new->prev = temp;
	}
}
