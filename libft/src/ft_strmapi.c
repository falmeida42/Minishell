/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:08:27 by fferreir          #+#    #+#             */
/*   Updated: 2021/08/23 14:06:19 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		x;
	char	*str;

	x = 0;
	if (!s)
		return (NULL);
	str = ft_strdup(s);
	if (!str)
		return (NULL);
	while (str[x])
	{
		str[x] = (*f)(x, s[x]);
		x++;
	}
	return (str);
}
