/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:57:48 by fferreir          #+#    #+#             */
/*   Updated: 2021/11/15 17:45:36 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct s_quote {
	int	first;
	int	next;
	int	x;
	int	y;
	int	z;
}	t_quote;

static int	count_splits(char *s, char c)
{
	t_quote	quote;
	int		x;
	int		count;

	x = 0;
	count = 0;
	while (s[x])
	{
		while (s[x] && s[x] == c)
			x++;
		if (!s[x])
			break ;
		while (s[x] && s[x] != c)
			x++;
		quote.first = find_quote(s, x);
		quote.next = find_quote(s, find_quote(s, x + 1));
		if (x >= quote.first && x <= quote.next)
		{
			while (x <= find_quote(s, find_quote(s, x + 1)))
				x++;
		}
		count++;
	}
	return (count);
}

static int	sub_l(char *s, char c, int x)
{
	t_quote	quote;
	int		count;

	quote.first = find_quote(s, x);
	quote.next = find_quote(s, find_quote(s, x + 1));
	count = 0;
	if (x >= quote.first && x <= quote.next)
	{
		while (x <= quote.next)
		{
			count++;
			x++;
		}
	}
	else
	{
		while (s[x] && s[x] != c)
		{
			count++;
			x++;
		}
	}
	return (count);
}

char	**fill_str(t_quote *q, char *s, char **split, char c)
{
	q->first = find_quote(s, q->x);
	q->next = find_quote(s, find_quote(s, q->x + 1));
	while (s[q->x] && s[q->x] != c)
	{
		if (q->x >= q->first && q->x <= q->next)
		{
			while (q->x <= q->next)
				split[q->y][q->z++] = s[q->x++];
		}
		else
			split[q->y][q->z++] = s[q->x++];
	}
	split[q->y][q->z] = '\0';
	return (split);
}

static char	**split_func(char **split, char *s, char c)
{
	t_quote	q;

	q.x = 0;
	q.y = 0;
	while (s[q.x])
	{
		q.z = 0;
		while (s[q.x] && s[q.x] == c)
			q.x++;
		if (s[q.x] && s[q.x] != c)
		{
			split[q.y] = (char *)ft_calloc(sub_l(s, c, q.x) + 1, sizeof(char));
			fill_str(&q, s, split, c);
			q.y++;
		}
	}
	split[q.y] = 0;
	return (split);
}

char	**ft_split(const char *s, char c)
{
	char	**split;
	char	*str;
	int		splits;

	if (!s || c < 0)
		return (NULL);
	if (!ft_strrchr(s, c))
	{
		split = (char **)malloc(sizeof(char *) * 2);
		split[0] = ft_strdup(s);
		split[1] = NULL;
		return (split);
	}
	str = (char *)s;
	splits = count_splits((char *)s, c);
	split = (char **)ft_calloc((splits + 1), sizeof(char *));
	if (!split)
		return (NULL);
	split_func(split, str, c);
	return (split);
}
