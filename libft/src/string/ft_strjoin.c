/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 03:42:08 by jceia             #+#    #+#             */
/*   Updated: 2021/11/15 21:32:47 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*res;

	if (s2 == NULL)
		return (ft_strdup(s1));
	size = ft_strlen(s1);
	size += ft_strlen(s2);
	res = malloc(size + 1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	ft_strcat(res, s1);
	ft_strcat(res, s2);
	return (res);
}
