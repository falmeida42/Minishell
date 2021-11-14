/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:53:50 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/14 17:53:53 by jpceia           ###   ########.fr       */
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
void token_free(void *ptr)
{
	t_token *token;

	token = (t_token *)ptr;
	free(token->value);
	free(token);
}
