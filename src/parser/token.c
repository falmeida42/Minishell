/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:53:50 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/16 09:33:28 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// allocates a new token
t_token	*token_new(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->value = value;
	return (token);
}

// free a token
void	token_free(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	free(token->value);
	free(token);
}

// goes and returns the next token in a token list
t_token	*token_iterator_next(t_token_list *it)
{
	it = it->next;
	return (it->content);
}

// Checks if a token is a word ( simple text, quoted text, double quoted text )
bool	is_word_token(t_token *token)
{
	t_token_type	type;

	type = token->type;
	return (type == TOKEN_TEXT
		|| type == TOKEN_QUOTED
		|| type == TOKEN_DQUOTED);
}

// Checks if a token is a redirection token ( > , >> , < , << )
bool	is_redirection_token(t_token *token)
{
	t_token_type	type;

	type = token->type;
	return (type == TOKEN_GREATER
		|| type == TOKEN_DGREATER
		|| type == TOKEN_LESS
		|| type == TOKEN_DLESS);
}
