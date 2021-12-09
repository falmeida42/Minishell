/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:33:02 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/07 19:33:34 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*take_twochar_symbol(t_char_iterator *cursor)
{
	t_token	*token;

	if (!ft_strncmp(*cursor, "||", 2))
		token = token_new(TOKEN_OR, ft_strdup("||"));
	else if (!ft_strncmp(*cursor, "&&", 2))
		token = token_new(TOKEN_AND, ft_strdup("&&"));
	else if (!ft_strncmp(*cursor, ">>", 2))
		token = token_new(TOKEN_DGREATER, ft_strdup(">>"));
	else if (!ft_strncmp(*cursor, "<<", 2))
		token = token_new(TOKEN_DLESS, ft_strdup("<<"));
	else
		return (NULL);
	char_iterator_next(cursor);
	char_iterator_next(cursor);
	return (token);
}

t_token	*take_symbol(t_char_iterator *cursor)
{
	t_token			*token;
	char			c;

	token = take_twochar_symbol(cursor);
	if (token)
		return (token);
	c = char_iterator_peek(cursor);
	if (c == '|')
		token = token_new(TOKEN_PIPE, ft_strdup("|"));
	else if (c == '>')
		token = token_new(TOKEN_GREATER, ft_strdup(">"));
	else if (c == '<')
		token = token_new(TOKEN_DLESS, ft_strdup("<"));
	else if (c == '(')
		token = token_new(TOKEN_LPAREN, ft_strdup("("));
	else if (c == ')')
		token = token_new(TOKEN_RPAREN, ft_strdup(")"));
	else
		token = NULL;
	char_iterator_next(cursor);
	return (token);
}
