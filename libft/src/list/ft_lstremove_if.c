/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_if.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 16:47:29 by jceia             #+#    #+#             */
/*   Updated: 2021/12/11 10:04:31 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstremove_if(t_list **begin_list, int (*f)(void *),
			void (*free_fct)(void *))
{
	t_list	*lst;
	t_list	*lst_prev;
	t_list	*lst_next;

	lst = *begin_list;
	lst_prev = 0;
	while (lst)
	{
		if (f(lst->content))
		{
			if (lst_prev)
				lst_prev->next = lst->next;
			else
				*begin_list = lst->next;
			lst_next = lst->next;
			free_fct(lst->content);
			free(lst);
		}
		else
		{
			lst_prev = lst;
			lst_next = lst->next;
		}
		lst = lst_next;
	}
}
