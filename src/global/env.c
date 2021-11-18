/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:29:46 by jceia             #+#    #+#             */
/*   Updated: 2021/11/17 01:18:54 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Functions to manipulate the global environment variable
 */

int	env_unset(char *key)
{
	return (map_del(&mini.env, key));
}

t_map	*env_set(char *key, char *value)
{
	return (map_set(&mini.env, ft_strdup(key), value));
}

char	*env_get(char *key)
{
	return (map_get_value(mini.env, key));
}
