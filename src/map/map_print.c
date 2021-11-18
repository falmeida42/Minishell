/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 02:48:24 by jceia             #+#    #+#             */
/*   Updated: 2021/11/16 16:48:24 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdio.h>

// Prints the map to the console.
void	map_print(t_map *map, char sep)
{
	t_pair	*p;

	while (map)
	{
		p = (t_pair *)map->content;
		ft_putstr(p->key);
		ft_putchar(sep);
		ft_putendl(p->value);
		map = map->next;
	}
}
