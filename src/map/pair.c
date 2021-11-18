/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 02:45:45 by jceia             #+#    #+#             */
/*   Updated: 2021/11/16 16:48:57 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdio.h>

// Convert a t_pair to a string, separated by a given delimiter.
char	*pair_to_str(t_pair *p, char sep)
{
	int		size_key;
	int		size;
	char	*s;

	if (!p)
		return (NULL);
	size_key = ft_strlen(p->key);
	size = size_key + ft_strlen(p->value) + 1;
	s = malloc(size + 1);
	if (!s)
		return (NULL);
	s[0] = '\0';
	ft_strcat(s, p->key);
	s[size_key] = sep;
	s[size_key + 1] = '\0';
	ft_strcat(s, p->value);
	return (s);
}

/*
 * Convert a string to a t_pair, assuming the string is separated by a given
 * delimiter.
 */
t_pair	*pair_from_str(char *s, char sep)
{
	char	*sep_pos;
	t_pair	*p;

	p = (t_pair *)malloc(sizeof(t_pair));
	if (!p)
		return (NULL);
	sep_pos = ft_strchr(s, sep);
	if (!sep_pos)
		return (NULL);
	p->key = ft_substr(s, 0, sep_pos - s);
	p->value = ft_strdup(sep_pos + 1);
	return (p);
}

// Free a t_pair.
void	pair_clear(void *ptr)
{
	t_pair	*p;

	p = (t_pair *)ptr;
	if (p->key)
	{
		free(p->key);
		p->key = NULL;
	}
	if (p->value)
	{
		free(p->value);
		p->value = NULL;
	}
	free(p);
}

// Gets the key from a t_pair.
char	*pair_key(t_pair *p)
{
	if (!p)
		return (NULL);
	return (p->key);
}

// Gets the value from a t_pair.
char	*pair_value(t_pair *p)
{
	if (!p)
		return (NULL);
	return (p->value);
}
