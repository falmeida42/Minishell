/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_star.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:32:27 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/06 18:54:34 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

// checks if a string matches with a another string with wildcard '*'
int str_match_star(char *s, char *s_star)
{
	int i = 0; 
	int j = 0;

	while (s[i] != '\0')
	{
		if (s_star[j] == '*')
		{
			if (s_star[j + 1] == '\0')
				return (1);
			while (s[i] != '\0' && s[i] != s_star[j + 1])
				i++;
			j++;
		}
		else if (s[i] != s_star[j])
			return (0);
		i++;
		j++;
	}
	return (1);
}

bool	is_file_or_directory(struct dirent *entry)
{
	if (!entry)
		return (false);
	return (entry->d_type == '\b' || entry->d_type == '\004');
}

// checks which files in a directory match with a string with wildcard '*'
t_list *match_files(char *to_match, char *dir)
{
	DIR *d;
	struct dirent *entry;
	t_list *files;

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
		if (entry->d_name && entry->d_name[0] == '.')
			continue ;
		if (str_match_star(entry->d_name, to_match))
			ft_lstpush_back(&files, ft_strdup(entry->d_name));
	}
	closedir(d);
	return (files);
}

void	apply_star_expander(t_token_list *lst)
{
	t_token	*token;
	t_list	*files_start;
	t_list	*files;
	
	while (lst)
	{
		token = (t_token *)lst->content;
		if (is_word_token(token) && ft_contains('*', token->value))
		{
			files_start = match_files(token->value, ".");
			if (files_start)
			{
				ft_lstsort(&files_start, ft_strcmp);
				files = files_start;
				token = token_new(TOKEN_QUOTED, ft_strdup(files->content));
				lst->content = token;
				files = files->next;
				while (files)
				{
					token = token_new(TOKEN_QUOTED, ft_strdup(files->content));
					ft_lstinsert_at(lst, token);
					files = files->next;
				}
				ft_lstclear(&files_start, NULL);
			}
		}
		lst = lst->next;
	}
}
