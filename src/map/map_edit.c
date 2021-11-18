/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 06:23:14 by jceia             #+#    #+#             */
/*   Updated: 2021/11/05 18:39:05 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdio.h>

/*
 * Sets a map with a given value
 * If the key already exists, it will override the value (freing the old value
 * and the new key - which is an equal copy)
 * Otherwise, it will allocate a new key-value pair and add it to the map
 */
t_map	*map_set(t_map **map, char *key, char *value)
{
	t_pair	*p;

	p = map_get(*map, key);
	if (p)
	{
		free(key);
		free(p->value);
		p->value = value;
		return (*map);
	}
	p = (t_pair *)malloc(sizeof(*p));
	if (!p)
		return (NULL);
	p->key = key;
	p->value = value;
	ft_lstpush_back(map, p);
	return (*map);
}
