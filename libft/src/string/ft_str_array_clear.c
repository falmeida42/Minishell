/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_array_clear.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 18:29:45 by jceia             #+#    #+#             */
/*   Updated: 2021/11/19 18:41:21 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_str_array_clear(char **str_arr, int len)
{
	int	index;

	index = 0;
	if (len > 0)
	{
		while (index < len)
		{
			free(str_arr[index]);
			index++;
		}
	}
	else
	{
		while(str_arr[index])
		{
			free(str_arr[index]);
			index++;
		}
	}
	free(str_arr);
}
