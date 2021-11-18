/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:12:55 by jceia             #+#    #+#             */
/*   Updated: 2021/11/17 01:18:18 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "libft.h"

/*
 * PAIR FUNCTIONS
 *
 * A pair consists of a key and a value, both strings.
 */
typedef struct s_pair
{
	char	*key;
	char	*value;
}	t_pair;

char	*pair_to_str(t_pair *p, char sep);
t_pair	*pair_from_str(char *s, char sep);
void	pair_clear(void *p);
char	*pair_key(t_pair *p);
char	*pair_value(t_pair *p);

/*
 * MAP FUNCTIONS
 *
 * A map is a linked list of pairs.
 */
typedef t_list	t_map;

t_pair	*map_get(t_map *map, char *key);
char	*map_get_value(t_map *map, char *key);
int		map_del(t_map **map, char *key);
t_map	*map_set(t_map **map, char *key, char *value);

char	**map_to_str_array(t_map *map, char sep);
t_map	*map_from_str_array(char **arr, char sep);

void	map_print(t_map *map, char sep);

#endif
