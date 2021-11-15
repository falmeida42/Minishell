/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:16:51 by fferreir          #+#    #+#             */
/*   Updated: 2021/08/23 13:59:26 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	nbr;

	nbr = n;
	if (n == -2147483647 - 1)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0 && n != -2147483648)
	{
		nbr = -n;
		ft_putchar_fd('-', fd);
	}
	if (nbr > 9)
	{
		ft_putnbr_fd((nbr / 10), fd);
		ft_putnbr_fd((nbr % 10), fd);
	}
	else
		ft_putchar_fd((nbr + '0'), fd);
}
