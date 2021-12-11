/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_star.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:32:27 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/11 12:11:23 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

// check if a string matches with another string with wildcard '*'
// considering only the wildcards '*' outside of single quotes
// TODO: consider escaped chars
bool	str_match_star_quotes(char *s, char *pattern, t_quote_type state)
{
	if (*s == '\0' && *pattern == '\0')
		return (true);
	if (state == QUOTE_NONE && *pattern == '\'')
		return (str_match_star_quotes(s, pattern + 1, QUOTE_SINGLE));
	if (state == QUOTE_NONE && *pattern == '"')
		return (str_match_star_quotes(s, pattern + 1, QUOTE_DOUBLE));
	if (state == QUOTE_SINGLE && *pattern == '\'')
		return (str_match_star_quotes(s, pattern + 1, QUOTE_NONE));
	if (state == QUOTE_DOUBLE && *pattern == '"')
		return (str_match_star_quotes(s, pattern + 1, QUOTE_NONE));
	if (*pattern != '*' || state == QUOTE_SINGLE || state == QUOTE_DOUBLE)
	{
		if (*s != *pattern)
			return (false);
		return (str_match_star_quotes(s + 1, pattern + 1, state));
	}
	if (str_match_star_quotes(s, pattern + 1, state))
		return (true);
	if (*s && str_match_star_quotes(s + 1, pattern, state))
		return (true);
	return (false);
}

// checks if a string matches with a another string with wildcard '*'
int	str_match_star(char *s, char *pattern)
{
	return (str_match_star_quotes(s, pattern, QUOTE_NONE));
}

// checks which files in a directory match with a string with wildcard '*'
// (entry->d_type == '\b' || entry->d_type == '\004') := is file or directory
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
		if (!(entry->d_type == DT_DIR || entry->d_type == DT_REG))
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
		token = token_new(TOKEN_TEXT, ft_strdup(files->content));
		token_free(lst->content);
		lst->content = token;
		files = files->next;
		while (files)
		{
			token = token_new(TOKEN_TEXT, ft_strdup(files->content));
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
		if (token->type == TOKEN_TEXT
			&& ft_contains_unquoted(token->value, '*'))
		{
			files = match_files(token->value, ".");
			ft_lstsort(&files, ft_strcmp);
			lst = insert_files_in_token_list(lst, files);
			ft_lstclear(&files, free);
		}
		lst = lst->next;
	}
}
