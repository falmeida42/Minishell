/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 19:10:07 by jceia             #+#    #+#             */
/*   Updated: 2021/12/06 16:23:39 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/resource.h>

int	ft_get_next_line(int fd, char **line)
{
	int		nb;
	char	c;

	if (fd < 0 || fd >= RLIMIT_NOFILE || !line)
		return (-1);
	*line = ft_strdup("");
	if (!*line)
		return (-1);
	while (1)
	{
		nb = read(fd, &c, 1);
		if (nb <= 0 || c == '\n')
			break ;
		*line = ft_straddc(*line, c);
	}
	return (nb);
}
