/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 14:18:38 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/13 10:40:10 by jceia            ###   ########.fr       */
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

bool	is_executable_verbose(char *full_path, char *path)
{
	struct stat	buf;

	if (access(full_path, X_OK) < 0)
	{
		perror(path);
		return (false);
	}
	if (stat(full_path, &buf) == 0 && S_ISDIR(buf.st_mode))
	{
		ft_putstr_error(path);
		ft_putendl_error(": is a directory");
		return (false);
	}
	if (stat(full_path, &buf) == 0 && !(buf.st_mode & S_IXUSR))
	{
		ft_putstr_error(path);
		ft_putendl_error(": permission denied");
		return (false);
	}
	return (true);
}
