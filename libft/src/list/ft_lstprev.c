/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 08:57:06 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/02 09:49:51 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstprev(t_list *lst, void *data)
{
	t_list	*prev;

	if (!lst)
		return (NULL);
	if (!data)
		return (ft_lstlast(lst));
	prev = lst;
	while (prev && prev->next)
	{
		if (prev->next->content == data)
			return (prev);
		prev = prev->next;
	}
	return (NULL);
}
