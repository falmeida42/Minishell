/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:36:18 by falmeida          #+#    #+#             */
/*   Updated: 2021/11/18 03:08:15 by jpceia           ###   ########.fr       */
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

/**
char	*get_path(t_cd *cd)
{
	char	*path;
	int		i;

	i = 1;
	path = ft_strjoin("/", g_mini.argv[i]);
	while (g_mini.argv[i + 1] != NULL)
	{
		path = ft_strjoin(path , " ");
		path = ft_strjoin(path , g_mini.argv[i + 1]);
		i++;
	}
	path = ft_strjoin(cd->pwd , path);
	return (path);
}

void	change_path(t_cd *cd)
{
	char	*str;

	str = NULL;
	str = getcwd(str, PATH_MAX);
	cd->tmp = g_mini.env;				// ???
	cd->pwd = ft_strdup(str);
	cd->path1 = get_path(cd);
	chdir(cd->path1);
	map_set(&g_mini.env, ft_strdup("PWD"), cd->path1);
	map_set(&g_mini.env, ft_strdup("OLDPWD"), cd->pwd);
}
*/

void	change_directory(char *dir)
{
	if (chdir(dir) < 0)
	{
		ft_putendl_error("cd: no such file or directory: ");
		return ; // 1
	}
	env_set("OLDPWD", ft_strdup(env_get("PWD")));
	env_set("PWD", getcwd(NULL, 0));
	// return 0;
}

void	ft_cd(void)
{
	char	*dir;

	// check number of arguments
	// if > 1, print error message: "cd: too many arguments"
	dir = g_mini.argv[1];
	if (!dir)
	{
		dir = env_get("HOME");
		if (!dir)
		{
			ft_putendl_error("cd: HOME not set");
			return ; // 1
		}
	}
	else if (strcmp(dir, "-") == 0)
	{
		dir = env_get("OLDPWD");
		if (!dir)
		{
			ft_putendl_error("cd: OLDPWD not set");
			return ; // 1
		}
	}
	change_directory(dir);
	// return
}
