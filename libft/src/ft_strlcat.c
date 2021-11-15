/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:15:44 by fferreir          #+#    #+#             */
/*   Updated: 2021/08/23 14:04:49 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	x;
	size_t	y;
	size_t	src_size;
	size_t	dst_initsize;

	src_size = ft_strlen(src);
	dst_initsize = ft_strlen(dst);
	x = dst_initsize;
	y = 0;
	if (dst_initsize < (dstsize - 1) && dstsize > 0)
	{
		while (src[y] && (dst_initsize + y) < (dstsize - 1))
		{
			dst[x] = src[y];
			y++;
			x++;
		}
		dst[x] = '\0';
	}
	if (x >= dstsize)
		dst_initsize = dstsize;
	return (src_size + dst_initsize);
}
