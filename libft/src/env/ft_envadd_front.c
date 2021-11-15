/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:55:37 by fferreir          #+#    #+#             */
/*   Updated: 2021/11/15 20:18:39 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_envadd_front(t_env **lst, t_env *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
