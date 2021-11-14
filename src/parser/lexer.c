/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 02:15:09 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/14 06:06:44 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

int ft_contains(char *s, char c)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == c)
            return (1);
        i++;
    }
    return (0);
}

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

char char_iterator_peek(char_iterator *it)
{
    return (**it);
}

char char_iterator_next(char_iterator *it)
{
    return (*(++*it));
}

t_token *token_symbol_twochar_next(char_iterator *cursor)
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

t_token *token_symbol_next(char_iterator *cursor)
{
    t_token_type type;
    t_token *token;
    char c;
    
    token = token_symbol_twochar_next(cursor);
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

t_token *token_dquoted_next(char **cursor)
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

t_token *token_quoted_next(char **cursor)
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

t_token *token_text_next(char **cursor)
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

// get the next token
t_token *token_next(char **cursor)
{
    char c;

    c = char_iterator_peek(cursor);
    while (c && c == ' ') // skip spaces
        c = char_iterator_next(cursor);
    if (c == '\0')
        return NULL;
    if (ft_contains(";|&><", c))
        return (token_symbol_next(cursor));
    if (c == '"')
        return (token_dquoted_next(cursor));
    if (c == '\'')
        return (token_quoted_next(cursor));
    return (token_text_next(cursor));
}

t_token_list *lex(char *input)
{
    t_token *token;
    t_token_list *token_list;

    token_list = NULL;
    while (1)
    {
        token = token_next(&input);
        if (!token)
            break ;
        token_list_pushback(&token_list, token);
    }
    return (token_list);
}

int main(int argc, char **argv)
{
    t_token_list *token_list;
    t_token_list *token_it;

    if (argc != 2)
    {
        printf("usage: ./lexer <input>\n");
        return (1);
    }
    token_list = lex(argv[1]);
    token_it = token_list;
    while (token_it)
    {
        printf("%d: %s\n", token_it->token->type, token_it->token->value);
        token_it = token_it->next;
    }
    token_list_free(token_list);
    return (0);
}