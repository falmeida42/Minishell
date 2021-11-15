/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 19:14:02 by fferreir          #+#    #+#             */
/*   Updated: 2021/08/23 14:07:11 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *find, size_t len)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	if (find[0] == '\0')
		return ((char *)src);
	while (src[x] && x < len)
	{
		if (src[x] == find[0])
		{
			while (src[x + y] == find[y] && x + y < len)
			{
				y++;
				if (find[y] == '\0')
					return ((char *)&src[x]);
			}
		}
		x++;
	}
	return (NULL);
}
