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

/*
 * Find the full path to an executable file, from the PATH environment
 * variable.
 */
char	*lookup_full_path(char *path)
{
	char	*full_path;
	char	*env_paths;
	char	**dir_start;
	char	**dir;

	env_paths = env_get("PATH");
	if (!env_paths)
		env_paths = "";
	dir_start = ft_split(env_paths, ':');
	dir = dir_start;
	full_path = NULL;
	while (*dir)
	{
		full_path = path_join(*dir, path);
		if (access(full_path, X_OK) == 0)
			break ;
		free(full_path);
		dir++;
	}
	if (*dir == NULL)
	{
		perror(path);
		full_path = NULL;
	}
	ft_str_array_clear(dir_start, 0);
	return (full_path);
}

char	*normalize_path(char *path)
{
	char	*dir;
	
	if (!path || !*path)
		return ft_strdup("");
	if (*path == '/') // absolute path
		return ft_strdup(path);
	if (*path == '.') // relative path
	{
		dir = getcwd(NULL, 0);
		path = ft_strjoin(dir, path);
		free(dir);
		return (path);
	}
	return (lookup_full_path(path));
}
