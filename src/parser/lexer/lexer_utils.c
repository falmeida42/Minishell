/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:52:49 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/11 09:35:57 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_quote_type	update_quote_type(t_quote_type quote_type,
					char c, char prev_char)
{
	if (prev_char != '\\')
	{
		if (quote_type == QUOTE_NONE)
		{
			if (c == '\'')
				return (QUOTE_SINGLE);
			if (c == '\"')
				return (QUOTE_DOUBLE);
		}
		else if (quote_type == QUOTE_SINGLE && c == '\'')
			return (QUOTE_NONE);
		else if (quote_type == QUOTE_DOUBLE && c == '\"')
			return (QUOTE_NONE);
	}
	return (quote_type);
}

char	update_prev_char(char c, char prev_char)
{
	if (prev_char == '\\')
		return (0);
	return (c);
}

/* takes a text token and returns it
 * as a string, using the same rules as bash
 * i.e., it stops in the end of string or
 * space if it is outside quotes
 */
t_token	*take_text(char **cursor)
{
	char			c;
	char			prev_char;
	char			*start;
	t_quote_type	quote_type;

	start = *cursor;
	c = char_iterator_peek(cursor);
	prev_char = 0;
	quote_type = QUOTE_NONE;
	while (c)
	{
		quote_type = update_quote_type(quote_type, c, prev_char);
		if (quote_type == QUOTE_NONE && ft_contains(c, " \t\n\r|&><)("))
			break ;
		prev_char = update_prev_char(c, prev_char);
		c = char_iterator_next(cursor);
	}
	return (token_new(TOKEN_TEXT, ft_substr(start, 0, *cursor - start)));
}

bool	does_add_char(t_quote_type quote_type, char c, char prev_char)
{
	if (quote_type == QUOTE_NONE)
		return (!(c == '\\' || c == '\'' || c == '"') || prev_char == '\\');
	if (quote_type == QUOTE_SINGLE)
		return (!(c == '\\' || c == '\'') || prev_char == '\\');
	if (quote_type == QUOTE_DOUBLE)
		return (!(c == '\\' || c == '"') || prev_char == '\\');
	return (false);
}

/*
 * Cleans a string from quotes and escapes
 */
char	*clean_string(char *str)
{
	int				i;
	char			*clean;
	char			c;
	char			prev_char;
	t_quote_type	quote_type;

	prev_char = 0;
	quote_type = QUOTE_NONE;
	clean = ft_strdup("");
	i = 0;
	while (str[i])
	{
		c = str[i];
		quote_type = update_quote_type(quote_type, c, prev_char);
		if (does_add_char(quote_type, c, prev_char))
			clean = ft_straddc(clean, c);
		prev_char = update_prev_char(c, prev_char);
		i++;
	}
	free(str);
	return (clean);
}
