/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:35:56 by fferreir          #+#    #+#             */
/*   Updated: 2021/08/23 14:10:37 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	x;
	size_t	size;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		size = ft_strlen(s) + 1;
	else
		size = len + 1;
	sub = (char *)ft_calloc(size, sizeof(char));
	if (!sub)
		return (NULL);
	x = 0;
	if ((size_t)start >= ft_strlen(s))
		return (sub);
	while (s[start] && x < len)
		sub[x++] = s[start++];
	sub[x] = '\0';
	return (sub);
}
