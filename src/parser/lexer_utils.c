/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:52:49 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/16 01:43:27 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

t_token	*take_twochar_symbol(t_char_iterator *cursor)
{
	t_token_type	type;

	type = TOKEN_NULL;
	if (!ft_strncmp(*cursor, "||", 2))
		type = TOKEN_OR;
	else if (!ft_strncmp(*cursor, "&&", 2))
		type = TOKEN_AND;
	else if (!ft_strncmp(*cursor, ">>", 2))
		type = TOKEN_DGREATER;
	else if (!ft_strncmp(*cursor, "<<", 2))
		type = TOKEN_DLESS;
	if (type == TOKEN_NULL)
		return (NULL);
	char_iterator_next(cursor);
	char_iterator_next(cursor);
	return (token_new(type, NULL));
}

t_token	*take_symbol(t_char_iterator *cursor)
{
	t_token_type	type;
	t_token			*token;
	char			c;

	token = take_twochar_symbol(cursor);
	if (token)
		return (token);
	c = char_iterator_peek(cursor);
	if (c == ';')
		type = TOKEN_SEMICOLON;
	else if (c == '|')
		type = TOKEN_PIPE;
	else if (c == '&')
		type = TOKEN_AMPERSAND;
	else if (c == '>')
		type = TOKEN_GREATER;
	else if (c == '<')
		type = TOKEN_LESS;
	else if (c == '(')
		type = TOKEN_LPAREN;
	else if (c == ')')
		type = TOKEN_RPAREN;
	char_iterator_next(cursor);
	token = token_new(type, NULL);
	return (token);
}

t_token	*take_dquoted(char **cursor)
{
	char	c;
	char	prev_char;
	char	*start;
	char	*end;

	char_iterator_next(cursor);
	start = *cursor;
	prev_char = 0;
	c = char_iterator_peek(cursor);
	while (c && (c != '"' || prev_char == '\\'))
	{
		prev_char = c;
		c = char_iterator_next(cursor);
	}
	end = *cursor;
	char_iterator_next(cursor);
	return (token_new(TOKEN_DQUOTED, ft_substr(start, 0, end - start)));
}

t_token	*take_quoted(char **cursor)
{
	char	c;
	char	prev_char;
	char	*start;
	char	*end;

	char_iterator_next(cursor);
	start = *cursor;
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

	start = *cursor;
	c = char_iterator_peek(cursor);
	while (c && !ft_contains(c, " ;|&><)("))
		c = char_iterator_next(cursor);
	end = *cursor;
	return (token_new(TOKEN_TEXT, ft_substr(start, 0, end - start)));
}
