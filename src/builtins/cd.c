/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:36:18 by falmeida          #+#    #+#             */
/*   Updated: 2021/12/09 18:45:29 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Change  the current directory to dir.
 * If dir is not supplied, the value of the HOME shell variable is the default.
 * Any additional arguments following dir are  ignored.
 * 
 * The variable  CDPATH defines the search path for the directory containing
 * dir: each directory name in CDPATH is searched for dir.
 * Alternative directory names in CDPATH are  separated  by  a colon (:).
 * A null directory name in CDPATH is the same as the current directory, i.e.,
 * ``.''.
 * 
 * If dir begins with a slash (/), then CDPATH is  not used.
 * If  .. appears in dir, it is processed by removing the immediately previous
 * pathname component from dir, back to a slash or the beginning of dir.
 *
 * An argument of - is converted  to  $OLDPWD  before the  directory  change
 * is  attempted.  If a non-empty directory name from CDPATH is used, or if -
 * is the first argument, and the directory change is successful, the absolute
 * pathname of the new working directory is written to the standard output.
 * The return value is true if the directory was successfully changed;
 * false otherwise.
 */

int	change_directory(char *dir)
{
	char	*pwd;

	pwd = env_get("PWD");
	if (!pwd)
		pwd = getcwd(NULL, PATH_MAX);
	if (chdir(dir) < 0)
	{
		ft_putstr_error("cd: ");
		perror(dir);
		return (1);
	}
	env_set(ft_strdup("OLDPWD"), ft_strdup(pwd));
	env_set(ft_strdup("PWD"), getcwd(NULL, 0));
	return (0);
}

int	ft_cd(char **argv, int fd)
{
	char	*dir;

	(void)fd;
	dir = argv[1];
	if (!dir)
	{
		dir = env_get("HOME");
		if (!dir)
		{
			ft_putendl_error("cd: HOME not set");
			return (1);
		}
	}
	else if (strcmp(dir, "-") == 0)
	{
		dir = env_get("OLDPWD");
		if (!dir)
		{
			ft_putendl_error("cd: OLDPWD not set");
			return (1);
		}
		ft_putendl_fd(dir, fd);
	}
	return (change_directory(dir));
}
