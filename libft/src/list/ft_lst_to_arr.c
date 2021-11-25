/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:04:15 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/25 02:41:08 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_lst_to_arr(t_list *lst)
{
	char	**arr;
	int		size;
	int		index;

	size = ft_lstsize(lst);
	arr = (char **)malloc(sizeof(*arr) * (size + 1));
	index = 0;
	while (lst)
	{
		arr[index] = lst->content;
		index++;
		lst = lst->next;
	}
	arr[size] = NULL;
	return (arr);
}
