/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 16:19:40 by fferreir          #+#    #+#             */
/*   Updated: 2021/11/15 19:38:51 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_env	*ft_lstmap(t_env *lst, void *(*f)(void*), void (*del)(void*))
{
	t_env	*new;
	t_env	*temp;

	if (!lst || !f || !del)
		return (NULL);
	new = ft_envnew(f(lst->content));
	if (!new)
		return (NULL);
	temp = new;
	lst = lst->next;
	while (lst)
	{
		temp->next = ft_envnew(f(lst->content));
		if (!temp->next)
		{
			ft_envclear(&new, del);
			return (NULL);
		}
		temp = temp->next;
		lst = lst->next;
	}
	return (new);
}
