/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_level_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 23:56:24 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/04 09:47:47 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Returns the size of the largest branch passed as argument.
 * @param	root	the root of the tree.
 * @return	int		the size of the largest branch.
 */
int	btree_level_count(t_btree *root)
{
	int	left_level_count;
	int	right_level_count;

	if (!root)
		return (0);
	left_level_count = btree_level_count(root->left);
	right_level_count = btree_level_count(root->right);
	if (left_level_count > right_level_count)
		return (left_level_count + 1);
	return (right_level_count + 1);
}
