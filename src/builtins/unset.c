/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:48:40 by fferreir          #+#    #+#             */
/*   Updated: 2021/12/13 13:01:09 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * For each name, remove the corresponding environment variable.
 * The exit status is true unless a name is readonly.
 */

int	ft_unset(char **argv, int fd)
{
	(void)fd;
	if (argv[1])
		env_unset(argv[1]);
	return (0);
}
