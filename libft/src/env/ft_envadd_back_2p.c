#include "libft.h"

void	ft_envadd_back_2p(t_env **lst, t_env *new)
{
	t_env *temp;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		temp = ft_envlast(*lst);
		temp->next = new;
		new->prev = temp;
	}
}
