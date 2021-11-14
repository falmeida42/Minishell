/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 02:15:09 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/14 06:17:50 by jpceia           ###   ########.fr       */
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
        return (take_symbol(cursor));
    if (c == '"')
        return (take_dquoted(cursor));
    if (c == '\'')
        return (take_quoted(cursor));
    return (take_text(cursor));
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