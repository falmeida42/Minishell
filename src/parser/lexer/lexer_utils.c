/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:52:49 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/10 22:14:10 by jpceia           ###   ########.fr       */
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

bool	ft_contains_unquoted(char *str, char needle)
{
	int				i;
	char			prev_char;
	t_quote_type	quote_type;

	i = 0;
	prev_char = 0;
	quote_type = QUOTE_NONE;
	while (str[i])
	{
		quote_type = update_quote_type(quote_type, str[i], prev_char);
		if (quote_type != QUOTE_SINGLE && str[i] == needle && prev_char != '\\')
			return (true);
		prev_char = str[i++];
	}
	return (false);
}

char	*ft_strchr_unquoted(char *str, char needle)
{
	int				i;
	char			prev_char;
	t_quote_type	quote_type;

	i = 0;
	prev_char = 0;
	quote_type = QUOTE_NONE;
	while (str[i])
	{
		quote_type = update_quote_type(quote_type, str[i], prev_char);
		if (quote_type != QUOTE_SINGLE && str[i] == needle && prev_char != '\\')
			return (&str[i]);
		prev_char = str[i++];
	}
	return (NULL);
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
		prev_char = c;
		c = char_iterator_next(cursor);
	}
	return (token_new(TOKEN_TEXT, ft_substr(start, 0, *cursor - start)));
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
	c = str[i];
	while (c)
	{
		quote_type = update_quote_type(quote_type, c, prev_char);
		if (quote_type == QUOTE_NONE)
		{
			// skip \ except if it is escaped
			if (!(c == '\\' || c == '\'' || c == '"') || prev_char == '\\')
				clean = ft_straddc(clean, c);
		}
		else if (quote_type == QUOTE_SINGLE)
		{
			if (!(c == '\\' || c== '\'') || prev_char == '\\')
				clean = ft_straddc(clean, c);
		}
		else if (quote_type == QUOTE_DOUBLE)
		{
			// skip \ except if it is escaped
			// skip " except if it is escaped
			if (!(c == '\\' || c == '"') || prev_char == '\\')
				clean = ft_straddc(clean, c);
		}
		prev_char = c;
		c = str[++i];
	}
	free(str);
	return (clean);
}