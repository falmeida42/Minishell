/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 06:14:30 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/14 06:18:07 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

char *ft_substr(char *s, int start, int len)
{
    char *sub;
    int i;

    i = 0;
    if (!s)
        return (NULL);
    if (!(sub = malloc(sizeof(char) * (len + 1))))
        return (NULL);
    while (i < len)
    {
        sub[i] = s[start + i];
        i++;
    }
    sub[i] = '\0';
    return (sub);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	x;

	x = 0;
	if (n == 0)
		return (0);
	while (s1[x] == s2[x] && s1[x] && s2[x] && x < (n - 1))
		x++;
	return ((unsigned char)(s1[x]) - (unsigned char)(s2[x]));
}

int ft_contains(char *s, char c);

t_token *take_twochar_symbol(char_iterator *cursor)
{
    t_token_type type;

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

t_token *take_symbol(char_iterator *cursor)
{
    t_token_type type;
    t_token *token;
    char c;
    
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
    char_iterator_next(cursor);
    token = token_new(type, NULL);
    return (token);
}

t_token *take_dquoted(char **cursor)
{
    char c;
    char prev_char;
    char *start;
    char *end;

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
    return (token_new(TOKEN_DQUOTED_TEXT, ft_substr(start, 0, end - start)));
}

t_token *take_quoted(char **cursor)
{
    char c;
    char prev_char;
    char *start;
    char *end;

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
    return (token_new(TOKEN_QUOTED_TEXT, ft_substr(start, 0, end - start)));
}

t_token *take_text(char **cursor)
{
    char c;
    char *start;
    char *end;
    
    start = *cursor;
    c = char_iterator_peek(cursor);
    while (c && !ft_contains(" ;|&><", c))
        c = char_iterator_next(cursor);
    end = *cursor;
    return (token_new(TOKEN_TEXT, ft_substr(start, 0, end - start)));    
}