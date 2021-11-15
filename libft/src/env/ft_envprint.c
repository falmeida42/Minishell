/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:31:53 by fferreir          #+#    #+#             */
/*   Updated: 2021/11/15 19:40:28 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_envprint(t_env *lst, char type)
{
	t_env	*head;

	head = lst;
	while (lst)
	{
		if (type == 'n' || type == 'a')
			printf("%s", (char *)lst->name);
		if (type == 'a')
			printf("=");
		if (type == 'c' || type == 'a')
			printf("%s\n", (char *)lst->content);
		if (type == 'd')
			ft_envnode_print_2p(lst);
		lst = lst->next;
	}
	lst = head;
}
