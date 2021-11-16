/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:50:36 by fferreir          #+#    #+#             */
/*   Updated: 2021/08/23 13:58:48 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst1;
	char	*src1;

	src1 = (char *)src;
	dst1 = (char *)dst;
	if (src1 < dst1)
	{
		src1 = src1 + (len - 1);
		dst1 = dst1 + (len - 1);
		while (len--)
		{
			*dst1 = *src1;
			dst1--;
			src1--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
