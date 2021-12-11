/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strwc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 18:18:51 by jceia             #+#    #+#             */
/*   Updated: 2021/12/11 13:16:23 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Word-Count function
 */
int	ft_strwc(char const *s, char c)
{
	int	count;
	int	prev_space;

	count = 0;
	prev_space = 1;
	while (*s)
	{
		if (*s == c)
			prev_space = 1;
		else if (prev_space)
		{
			count++;
			prev_space = 0;
		}
		s++;
	}
	return (count);
}

int	ft_strwc_seps(char const *s, char *charset)
{
	int	count;
	int	prev_space;

	count = 0;
	prev_space = 1;
	while (*s)
	{
		if (ft_contains(*s, charset))
			prev_space = 1;
		else if (prev_space)
		{
			count++;
			prev_space = 0;
		}
		s++;
	}
	return (count);
}
