/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:52:28 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/11 14:14:16 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

// get the next token
t_token	*token_next(char **cursor)
{
	char	c;

	c = char_iterator_peek(cursor);
	while (c && ft_isspace(c))
		c = char_iterator_next(cursor);
	if (c == '\0')
		return (NULL);
	if (ft_contains(c, "|&><)("))
		return (take_symbol(cursor));
	return (take_text(cursor));
}

t_token_list	*lex(char *input)
{
	t_token			*token;
	t_token_list	*token_list;

	token_list = NULL;
	while (1)
	{
		token = token_next(&input);
		if (token == NULL)
			break ;
		ft_lstpush_back(&token_list, token);
	}
	return (token_list);
}
