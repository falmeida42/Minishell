/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 18:29:58 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/18 21:14:24 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <dirent.h>

// checks if a string matches with a another string with wildcard '*'
int	str_match_star(char *s, char *s_star)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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

// checks which files in a directory match with a string with wildcard '*'
t_list	*match_files(char *to_match, char *dir)
{
	DIR				*d;
	struct dirent	*dir_entry;
	char			*file_name;
	t_list			*files;

	d = opendir(dir);
	files = NULL;
	if (d == NULL)
		return (NULL);
	while (1)
	{
		dir_entry = readdir(d);
		if (dir_entry == NULL)
			break ;
		file_name = dir_entry->d_name;
		if (str_match_star(file_name, to_match))
			ft_lstpush_back(&files, file_name);
	}
	closedir(d);
	return (files);
}

// checks if a text token starts with a tilde '~' and expands it
char	*expand_tilde(t_token *token)
{
	char	*home_dir;
	char	*expanded_str;

	if (token->type != TOKEN_TEXT)
		return (token->value);
	if (token->value[0] != '~')
		return (token->value);
	home_dir = getenv("HOME");
	if (home_dir == NULL)
		return (token->value);
	expanded_str = ft_strjoin(home_dir, token->value + 1);
	return (expanded_str);
}

t_list	*expand_star(t_token *token)
{
	t_list	*matches;

	if (token->type == TOKEN_TEXT)
	{
		matches = match_files(token->value, ".");
		if (matches == NULL)
			return (ft_lstnew(token->value));
		return (matches);
	}
	return (ft_lstnew(token->value));
}

// WIP
char	*expand_dollar(t_token *token)
{
	if (token->type == TOKEN_TEXT)
		return (token->value);
	if (token->type == TOKEN_DQUOTED)
		return (token->value);
	return (token->value);
}
