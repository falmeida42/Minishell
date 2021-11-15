/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:03:51 by fferreir          #+#    #+#             */
/*   Updated: 2021/08/23 14:04:40 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		len;
	int		x;
	int		y;

	if (!s2 || !s1)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	s3 = (char *)malloc(sizeof(*s1) * (len + 1));
	if (!s3)
		return (NULL);
	x = 0;
	y = 0;
	while (s1[x])
	{
		s3[x] = s1[x];
		x++;
	}
	while (s2[y])
	{
		s3[x + y] = s2[y];
		y++;
	}
	s3[x + y] = '\0';
	return (s3);
}
