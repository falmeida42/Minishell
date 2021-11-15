/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:35:57 by fferreir          #+#    #+#             */
/*   Updated: 2021/08/23 14:09:21 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkchr(const char *set, char c)
{
	int	x;

	x = 0;
	if (!set)
		return (0);
	while (set[x])
	{
		if (set[x] == c)
			return (1);
		x++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		x;
	int		y;
	int		z;

	x = 0;
	z = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[x] && ft_checkchr(set, s1[x]) == 1)
		x++;
	y = ft_strlen(s1);
	while (y > x && ft_checkchr(set, s1[y - 1]) == 1)
		y--;
	trimmed = (char *)malloc(sizeof(*s1) * (y - x + 1));
	if (!trimmed)
		return (NULL);
	while (x < y)
	{
		trimmed[z] = s1[x];
		z++;
		x++;
	}
	trimmed[z] = '\0';
	return (trimmed);
}
