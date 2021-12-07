/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:14:37 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/07 17:31:21 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks if a token is a word ( simple text, quoted text, double quoted text )
bool	is_word_token(t_token *token)
{
	t_token_type	type;

	if (!token)
		return (false);
	type = token->type;
	return (type == TOKEN_TEXT
		|| type == TOKEN_BREKETS
		|| type == TOKEN_QUOTED
		|| type == TOKEN_DQUOTED);
}

// Checks if a token is a redirection token ( > , >> , < , << )
bool	is_redirection_token(t_token *token)
{
	t_token_type	type;

	if (!token)
		return (false);
	type = token->type;
	return (type == TOKEN_GREATER
		|| type == TOKEN_DGREATER
		|| type == TOKEN_LESS
		|| type == TOKEN_DLESS);
}

// Checks if a token appears in a simple command (word or redirects)
bool	is_simple_command_token(t_token *token)
{
	return (is_word_token(token) || is_redirection_token(token));
}

// Checks if a token is empty word
bool	is_empty_word_token(t_token *token)
{
	if (!is_word_token(token))
		return (false);
	if (!token->value)
		return (true);
	return (token->value[0] == '\0');
}
