/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 01:54:19 by jceia             #+#    #+#             */
/*   Updated: 2021/12/11 17:50:35 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "libft.h"
#include <stdio.h>

// Converts a map to an array of strings.
char	**map_to_str_array(t_map *map, char sep)
{
	char	**arr;
	int		index;
	int		size;

	size = ft_lstsize(map);
	arr = (char **)malloc(sizeof(*arr) * (size + 1));
	if (!arr)
		return (NULL);
	arr[size] = NULL;
	index = 0;
	while (map)
	{
		arr[index++] = pair_to_str((t_pair *)map->content, sep);
		map = map->next;
	}
	return (arr);
}

char	*update_shlvl(char *shlvl)
{
	char	*holder;

	holder = shlvl;
	shlvl = ft_itoa(ft_atoi(shlvl) + 1);
	free(holder);
	return (shlvl);
}

// Generates a map from an array of strings.
t_map	*map_from_str_array(char **arr, char sep)
{
	t_pair	*p;
	t_map	*map;

	map = NULL;
	while (*arr)
	{
		p = pair_from_str(*arr, sep);
		++arr;
		if (!p)
			continue ;
		if (!ft_strcmp(p->key, "SHLVL"))
			p->value = update_shlvl(p->value);
		if (!ft_lstpush_back(&map, p))
		{
			ft_lstclear(&map, &pair_clear);
			return (NULL);
		}
	}
	return (map);
}
