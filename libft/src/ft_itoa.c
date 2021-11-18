/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:11:03 by fferreir          #+#    #+#             */
/*   Updated: 2021/08/23 13:53:18 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isneg(int n)
{
	int		neg;

	neg = 1;
	if (n < 0)
		neg = -1;
	return (neg);
}

static int	ft_nbrsize(int n)
{
	int		size;

	size = 0;
	while (n > 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static char	*ft_strrev(char *str)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	x = ft_strlen(str) - 1;
	while (y < ((x + 1) / 2))
	{
		c = str[y];
		str[y] = str[x - y];
		str[x - y] = c;
		y++;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*nbr;
	int		neg;
	int		x;

	x = 0;
	neg = ft_isneg(n);
	n = neg * n;
	if (n == -2147483647 - 1)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	nbr = (char *)ft_calloc((ft_nbrsize(n) + 2), sizeof(char));
	if (!nbr)
		return (NULL);
	while (n != 0)
	{
		nbr[x++] = (n % 10) + '0';
		n = n / 10;
	}
	if (neg == -1)
		nbr[x++] = '-';
	nbr = ft_strrev(nbr);
	nbr[x] = '\0';
	return (nbr);
}
