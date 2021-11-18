/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 23:52:16 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/17 20:17:33 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * @brief	Returns the first element related to the reference data given as
 *			argument.
 * @note	The tree is browsed using infix traversal.
 * @note	If the element isn’t found, the function returns NULL.
 * 
 * @param	root 		the root of the tree.
 * @param	data_ref	the reference data.
 * @param	cmpf		the comparison function.
 * @return	void*		the search result.
 */
void	*btree_search_item(t_btree *root, void *data_ref,
			int (*cmpf)(void *, void *))
{
	int		cmp_result;

	if (!root)
		return (NULL);
	cmp_result = cmpf(data_ref, root->item);
	if (cmp_result == 0)
		return (root->item);
	if (cmp_result < 0)
		return (btree_search_item(root->left, data_ref, cmpf));
	return (btree_search_item(root->right, data_ref, cmpf));
}
