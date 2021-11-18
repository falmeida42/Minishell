/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 23:29:21 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/17 20:35:17 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * @brief	Free the memory of a btree, including the content of each node.
 * 
 * @param	root	the root of the tree. 
 * @param	del		the function to be called to free the content of the nodes. 
 */
void	btree_clear(t_btree *root, void (*del)(void *))
{
	if (!root)
		return ;
	btree_clear(root->left, del);
	btree_clear(root->right, del);
	if (del)
		del(root->item);
	free(root);
}
