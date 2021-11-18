/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:21:33 by fferreir          #+#    #+#             */
/*   Updated: 2021/08/19 19:28:54 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	x;
	int	nbr;
	int	sign;

	x = 0;
	nbr = 0;
	sign = 1;
	while (str[x] == ' ' || str[x] == '\n' || str[x] == '\t'
		|| str[x] == '\v' || str[x] == '\r' || str[x] == '\f')
		x++;
	if (str[x] == '-' || str[x] == '+')
	{
		if (str[x] == '-')
			sign = -1;
		x++;
	}
	while (str[x] >= '0' && str[x] <= '9')
	{
		nbr = (str[x] - 48) + (10 * nbr);
		x++;
	}
	return (sign * nbr);
}
