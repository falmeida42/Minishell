/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 18:44:35 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/04 09:47:08 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcopy(t_list *lst)
{
	t_list	*copy;

	copy = NULL;
	while (lst)
	{
		ft_lstpush_back(&copy, lst->content);
		lst = lst->next;
	}
	return (copy);
}
