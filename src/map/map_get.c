/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:06:52 by jceia             #+#    #+#             */
/*   Updated: 2021/11/16 16:48:13 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdio.h>

// Returns the pair of key and value associated with the given key.
t_pair	*map_get(t_map *map, char *key)
{
	t_pair	*p;

	while (map)
	{
		p = (t_pair *)map->content;
		if (ft_strcmp(p->key, key) == 0)
			return (p);
		map = map->next;
	}
	return (NULL);
}

// Returns the value associated with the given key.
char	*map_get_value(t_map *map, char *key)
{
	t_pair	*p;

	p = map_get(map, key);
	if (p)
		return (p->value);
	return (NULL);
}

// Returns the value in a given pair.
char	*node_get_value(t_map *map)
{
	t_pair	*p;

	if (!map)
		return (NULL);
	p = map->content;
	if (!p)
		return (NULL);
	return (p->value);
}
