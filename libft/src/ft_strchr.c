/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 17:18:24 by fferreir          #+#    #+#             */
/*   Updated: 2021/08/23 14:03:06 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	x;

	x = 0;
	while (str[x] && str[x] != (const char)c)
	{
		x++;
	}
	if (str[x] == (char)c)
		return ((char *)&str[x]);
	return (NULL);
}
