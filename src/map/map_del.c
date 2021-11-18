/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:07:43 by jceia             #+#    #+#             */
/*   Updated: 2021/11/16 16:47:52 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

// Removes the first element of the map.
void	map_del_first(t_map **map)
{
	t_map	*node;

	node = *map;
	*map = (*map)->next;
	ft_lstdelone(node, pair_clear);
}

// Removes an element from the map, corresponding to the given key.
int	map_del(t_map **map, char *key)
{
	t_map	*node;
	t_map	*prev_node;

	if (!*map)
		return (0);
	if (ft_strcmp(pair_key((*map)->content), key) == 0)
	{
		map_del_first(map);
		return (1);
	}
	prev_node = *map;
	node = (*map)->next;
	while (node)
	{
		if (ft_strcmp(pair_key(node->content), key) == 0)
		{
			prev_node->next = node->next;
			ft_lstdelone(node, pair_clear);
			return (1);
		}
		prev_node = node;
		node = node->next;
	}
	return (0);
}
