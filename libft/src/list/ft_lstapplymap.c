/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstapplymap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:43:02 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/05 12:49:29 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstapplymap(t_list *lst, void *(*f)(void *))
{
	while (lst)
	{
		lst->content = f(lst->content);
		lst = lst->next;
	}
}
