#include "minishell.h"

void	swap(t_env *A, t_env *B, t_env *C)
{
	t_env *D;

	D = C->next;
	if (A != NULL)
		A->next = C;
	C->next = B;
	B->next = D;
	B->prev = C;
	C->prev = A;
	if (D != NULL)
		D->prev = B;
}

void	sorter(t_env *lst)
{
	int ret;

	while(lst->next != NULL)
	{
		ret = ft_strncmp(lst->name, lst->next->name, ft_strlen(lst->name));

		if (ret > 0 || (ret == 0 && ft_strlen(lst->name) > ft_strlen(lst->next->name)))
		{
			swap(lst->prev, lst, lst->next);
			break ;
		}
		lst = lst->next;
	}

}

bool	checker(t_env *lst)
{
	int ret;
	while (lst->next != NULL)
	{
		ret = ft_strncmp(lst->name, lst->next->name, ft_strlen(lst->name));
		if (ret > 0)
			return(false);
		lst = lst->next;
	}
	return(true);
}

t_env *duplicate_env(t_env *lst)
{
	t_env *temp;
	t_env *dup_lst;

	dup_lst = NULL;
	while (lst)
	{
		temp = ft_envdup_2p(lst);
		ft_envadd_back_2p(&dup_lst, temp);
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return(dup_lst);
}

int	env_sorted()
{
	t_env	*lst;

	lst = duplicate_env(mini.env);
	while (!checker(lst))
	{
		sorter(lst);
		lst = ft_envhead_2p(lst);
	}
	ft_envprint(lst, 'a');
	if (lst)
		free_dp_env(lst);
	return(1);
}
