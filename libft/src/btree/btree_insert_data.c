/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 23:27:08 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/17 20:17:33 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * @brief	Inserts the element item into a tree.
 * @details	The tree passed as argument will be sorted: for each node all
 * 			lower elements are located on the left side and all higher or
 * 			equal elements on the right.
 * 			We’ll also pass a comparison function similar to strcmp as
 * 			argument.
 * 
 * @param	root	the root of the tree.
 * @param	item	the item to insert.
 * @param	cmpf	the comparison function.
 */
void	btree_insert_data(t_btree **root, void *item,
			int (*cmpf)(void *, void *))
{
	if (!*root)
	{
		*root = btree_create_node(item);
		return ;
	}
	if (cmpf(item, (*root)->item) < 0)
		btree_insert_data(&(*root)->left, item, cmpf);
	else
		btree_insert_data(&(*root)->right, item, cmpf);
}
