/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 18:40:26 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/06 18:53:11 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstsort(t_list **begin_list, int (*cmp)(void *, void *))
{
	t_list	*l;
	t_list	*l_prev;
	t_list	*holder;

	if (begin_list || *begin_list)
		return ;
	l = *begin_list;
	l_prev = NULL;
	while (l->next)
	{
		if (cmp(l->content, l->next->content) < 0)
		{
			holder = l->next;
			l->next = l->next->next;
			holder->next = l;
			if (l_prev)
				l_prev->next = holder;
			else
				*begin_list = holder;
			ft_lstsort(begin_list, cmp);
			break ;
		}
		l_prev = l;
		l = l->next;
	}
}
