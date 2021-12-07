/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:53:50 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/07 17:32:18 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

	if (!ptr)
		return ;
	token = (t_token *)ptr;
	if (token->value)
		free(token->value);
	free(token);
}

// goes and returns the next token in a token list
t_token	*token_iterator_next(t_token_iterator *it)
{
	if (!it || !*it)
		return (NULL);
	*it = (*it)->next;
	if (!*it)
		return (NULL);
	return ((*it)->content);
}

t_token	*token_iterator_peek(t_token_iterator *it)
{
	if (!it || !*it)
		return (NULL);
	return ((*it)->content);
}
