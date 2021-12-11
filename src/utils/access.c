/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 14:18:38 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/11 14:29:22 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

bool	is_executable(char *path)
{
	struct stat	buf;

	if (access(path, X_OK) != 0)
		return (false);
	if (stat(path, &buf) != 0)
		return (false);
	if (!S_ISREG(buf.st_mode))
		return (false);
	return (true);
}
