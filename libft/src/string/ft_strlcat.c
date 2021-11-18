/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:21:52 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/15 21:32:23 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	n;
	size_t	m;
	size_t	index;

	n = ft_strlen(dest);
	m = ft_strlen(src);
	index = 0;
	while (src[index] && n + index + 1 < size)
	{
		dest[n + index] = src[index];
		index++;
	}
	dest[n + index] = 0;
	if (n < size)
		return (n + m);
	return (size + m);
}
