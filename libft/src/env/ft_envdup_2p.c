#include "libft.h"

t_env	*ft_envdup_2p(t_env *lst)
{
	t_env *new;

	new = (t_env*)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->name = lst->name;
	new->content = lst->content;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
