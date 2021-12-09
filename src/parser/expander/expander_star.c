/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_star.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:32:27 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/09 09:57:42 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

// checks if a string matches with a another string with wildcard '*'
int	str_match_star(char *s, char *pattern)
{
	if (*s == '\0' && *pattern == '\0')
		return (1);
	if (*pattern != '*')
	{
		if (*s != *pattern)
			return (0);
		return (str_match_star(s + 1, pattern + 1));
	}
	if (str_match_star(s, pattern + 1))
		return (1);
	if (*s && str_match_star(s + 1, pattern))
		return (1);
	return (0);
}

bool	is_file_or_directory(struct dirent *entry)
{
	if (!entry)
		return (false);
	return (entry->d_type == '\b' || entry->d_type == '\004');
}

// checks which files in a directory match with a string with wildcard '*'
t_list	*match_files(char *to_match, char *dir)
{
	DIR				*d;
	struct dirent	*entry;
	t_list			*files;

	d = opendir(dir);
	files = NULL;
	if (!d)
		return (NULL);
	while (1)
	{
		entry = readdir(d);
		if (!entry)
			break ;
		if (!is_file_or_directory(entry))
			continue ;
		if (entry->d_name[0] == '.')
			continue ;
		if (str_match_star(entry->d_name, to_match))
			ft_lstpush_back(&files, ft_strdup(entry->d_name));
	}
	closedir(d);
	return (files);
}

t_token_list	*insert_files_in_token_list(t_token_list *lst, t_list *files)
{
	t_token	*token;

	if (files)
	{
		ft_lstsort(&files, ft_strcmp);
		token = token_new(TOKEN_QUOTED, ft_strdup(files->content));
		lst->content = token;
		files = files->next;
		while (files)
		{
			token = token_new(TOKEN_QUOTED, ft_strdup(files->content));
			lst = ft_lstinsert_at(lst, token);
			files = files->next;
		}
	}
	return (lst);
}

void	apply_star_expander(t_token_list *lst)
{
	t_token	*token;
	t_list	*files;

	while (lst)
	{
		token = (t_token *)lst->content;
		if (token->type == TOKEN_TEXT && ft_contains('*', token->value))
		{
			files = match_files(token->value, ".");
			lst = insert_files_in_token_list(lst, files);
			ft_lstclear(&files, NULL);
		}
		lst = lst->next;
	}
}
