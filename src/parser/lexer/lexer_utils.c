/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:52:49 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/10 15:55:07 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	*remove_quotes(char *str)
{
	char	*str2;
	int		i;
	int		j;

	str2 = malloc(ft_strlen(str) + 1);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' && (i == 0 || str[i - 1] != '\\'))
			i++;
		else
			str2[j++] = str[i++];
	}
	str2[j] = '\0';
	free(str);
	return (str2);
}

int	only_char(char *str, char c)
{
	int	i;
	
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

t_token	*take_dquoted(char **cursor)
{
	char	c;
	char	prev_char;
	char	*start;
	char	*end;
	bool	inside_quotes;

	inside_quotes = true;
	start = *cursor;
	char_iterator_next(cursor);
	c = char_iterator_peek(cursor);
	prev_char = 0;
	end = NULL;
	if (only_char(start, '"'))
	{
		g_mini.parse_error = ft_strdup("minishell: permission denied: ");
		return (token_new(TOKEN_DQUOTED, ft_strdup(" ")));
	}
	while (c)
	{
		if (c == '"' && prev_char != '\\')
			inside_quotes = !inside_quotes;
		else if (c == ' ' && !inside_quotes)
			break ;
		prev_char = c;
		c = char_iterator_next(cursor);
	}
	if (end == NULL)
		end = *cursor;
	return (token_new(TOKEN_DQUOTED,
			remove_quotes(ft_substr(start, 0, end - start))));
}

t_token	*take_quoted(char **cursor)
{
	char	c;
	char	prev_char;
	char	*start;
	char	*end;

	char_iterator_next(cursor);
	start = *cursor;
	if (only_char(start, '\''))
	{
		g_mini.parse_error = ft_strdup("minishell: permission denied: ");
		return (token_new(TOKEN_DQUOTED, ft_strdup(" ")));
	}
	prev_char = 0;
	c = char_iterator_peek(cursor);
	while (c && (c != '\'' || prev_char == '\\'))
	{
		prev_char = c;
		c = char_iterator_next(cursor);
	}
	end = *cursor;
	char_iterator_next(cursor);
	return (token_new(TOKEN_QUOTED, ft_substr(start, 0, end - start)));
}

t_token	*take_text(char **cursor)
{
	char	c;
	char	*start;
	char	*end;
	char	*result;

	start = *cursor;
	c = char_iterator_peek(cursor);
	while (c && !ft_contains(c, " |&><)("))
		c = char_iterator_next(cursor);
	end = *cursor;
	result = ft_substr(start, 0, end - start);
	if (!ft_contains('\'', start) || !ft_contains('"', start))
		result = remove_quotes(result);
	return (token_new(TOKEN_TEXT, result));
}
