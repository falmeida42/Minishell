/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert_at.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:20:54 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/07 19:38:40 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstinsert_at(t_list *node, void *content)
{
	t_list	*node_new;

	node_new = ft_lstnew(content);
	if (!node_new)
		return (NULL);
	if (node->next)
		node_new->next = node->next;
	node->next = node_new;
	return (node_new);
}
