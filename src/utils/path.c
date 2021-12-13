/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   path.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jpceia <joao.p.ceia@gmail.com>			 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/11/25 02:17:54 by jpceia			#+#	#+#			 */
/*   Updated: 2021/11/25 03:46:06 by jpceia		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

char	*path_join(char *path, char *fname)
{
	char	*new_path;

	if (!path || !fname)
		return (NULL);
	new_path = malloc(sizeof(char) * (strlen(path) + strlen(fname) + 2));
	if (!new_path)
		return (NULL);
	new_path[0] = '\0';
	strcat(new_path, path);
	if (new_path[strlen(new_path) - 1] != '/')
		strcat(new_path, "/");
	strcat(new_path, fname);
	return (new_path);
}

char	*lookup_exe_in_directories(char *path, char **dir)
{
	char	*full_path;

	full_path = NULL;
	while (*dir)
	{
		full_path = path_join(*dir, path);
		if (is_executable(full_path))
			return (full_path);
		free(full_path);
		dir++;
	}
	return (NULL);
}

/*
 * Find the full path to an executable file, from the PATH environment
 * variable.
 */
char	*lookup_full_path(char *path)
{
	char	*full_path;
	char	*env_paths;
	char	**dir;

	env_paths = env_get("PATH");
	if (!env_paths)
		env_paths = "";
	dir = ft_split(env_paths, ':');
	full_path = lookup_exe_in_directories(path, dir);
	if (!full_path)
	{
		ft_putstr_error(path);
		ft_putendl_error(": command not found");
	}
	ft_str_array_clear(dir, 0);
	return (full_path);
}

char	*get_full_path(char *path)
{
	struct stat	sb;
	char		*full_path;
	char		*dir;

	dir = getcwd(NULL, 0);
	full_path = path_join(dir, path);
	free(dir);
	if (access(full_path, X_OK) < 0)
	{
		free(full_path);
		perror(path);
		return (NULL);
	}
	if (stat(full_path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		free(full_path);
		ft_putstr_error(path);
		ft_putendl_error(": is a directory");
		return (NULL);
	}
	return (full_path);
}

char	*normalize_path(char *path)
{
	struct stat	sb;

	if (!path)
		return (NULL);
	if (*path == '/')
	{
		if (access(path, X_OK) < 0)
		{
			perror(path);
			return (NULL);
		}
		if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		{
			ft_putstr_error(path);
			ft_putendl_error(": is a directory");
			return (NULL);
		}
		return (ft_strdup(path));
	}
	if (*path == '.')
		return (get_full_path(path));
	return (lookup_full_path(path));
}
