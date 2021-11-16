/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 17:18:48 by fferreir          #+#    #+#             */
/*   Updated: 2021/08/23 13:58:04 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			x;
	unsigned char	*str1;

	str1 = (unsigned char *)str;
	x = 0;
	while (x < n)
	{
		if (str1[x] == (unsigned char)c)
		{
			return ((unsigned char *)str + x);
		}
		x++;
	}
	return (NULL);
}
