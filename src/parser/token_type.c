/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:14:37 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/18 21:13:38 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// Checks if a token appears in a simple command (word or redirects)
bool	is_simple_command_token(t_token *token)
{
	return (is_word_token(token) || is_redirection_token(token));
}
