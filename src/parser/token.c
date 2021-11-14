/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 03:35:51 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/14 04:34:17 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// allocates a new token
t_token *token_new(t_token_type type, char *value)
{
    t_token *token;
    
    token = malloc(sizeof(t_token));
    if (token == NULL)
        return (NULL);
    token->type = type;
    token->value = value;
    return (token);
}

// free a token
void token_free(t_token *token)
{
    free(token->value);
    free(token);
}

// REPLACE THE CODE BELLOW WITH A GENERIC LINKED LIST

// initialize a token_list
t_token_list *token_list_new(t_token *token)
{
    t_token_list *list;
    
    list = malloc(sizeof(t_token_list));
    if (list == NULL)
        return (NULL);
    list->token = token;
    list->next = NULL;
    return (list);
}

// free a token_list
void token_list_free(t_token_list *list)
{
    if (list->next)
        token_list_free(list->next);
    token_free(list->token);
    free(list);
}

// push back a token to the list
t_token_list *token_list_pushback(t_token_list **list, t_token *token)
{
    t_token_list *new;
    t_token_list *node;

    new = token_list_new(token);
    if (new == NULL)
        return (NULL);
    if (*list == NULL)
        *list = new;
    else
    {
        node = *list;
        while (node->next)
            node = node->next;
        node->next = new;
    }
    return new;
}

// get the token_list size
int token_list_size(t_token_list *list)
{
    int size;

    size = 0;
    while (list)
    {
        ++size;
        list = list->next;
    }
    return (size);
}