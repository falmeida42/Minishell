/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 02:48:24 by jceia             #+#    #+#             */
/*   Updated: 2021/12/06 16:56:27 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdio.h>

// Prints the map to the console.
void	map_print_fd(t_map *map, char sep, int fd)
{
	t_pair	*p;

	while (map)
	{
		p = (t_pair *)map->content;
		ft_putstr_fd(p->key, fd);
		ft_putchar_fd(sep, fd);
		ft_putendl_fd(p->value, fd);
		map = map->next;
	}
}
