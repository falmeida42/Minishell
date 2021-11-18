/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 01:47:24 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/18 03:05:47 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	simple_cmd_parse_redirection_token(
	t_simple_command *cmd, t_token_iterator *it)
{
	t_token			*token;
	t_token_type	type;

	token = (*it)->content;
	type = token->type;
	token = token_iterator_next(it);
	if (token == NULL)
		return ;
	if (type == TOKEN_GREATER)
		cmd->outfile = token->value;
	else if (type == TOKEN_DGREATER)
	{
		cmd->outfile = token->value;
		cmd->append = true;
	}
	else if (type == TOKEN_LESS)
		cmd->infile = token->value;
	else if (type == TOKEN_DLESS)
	{
		cmd->infile = token->value;
		cmd->here_doc = true;
	}
}

t_simple_command	*simple_cmd_parse(t_token_iterator *it)
{
	t_simple_command	*cmd;
	t_token				*token;

	cmd = ft_calloc(1, sizeof(*cmd));
	while (*it)
	{
		token = (*it)->content;
		if (is_word_token(token))
			ft_lstpush_back(&cmd->argv, token->value);
		else if (is_redirection_token(token))
			simple_cmd_parse_redirection_token(cmd, it);
		else
			break ;
		token_iterator_next(it);
	}
	return (cmd);
}

// TODO: check if there are consecutive pipes
t_command	*command_parse(t_token_iterator *it)
{
	t_token		*token;
	t_command	*command;

	command = NULL;
	while (*it)
	{
		token = (*it)->content;
		if (is_simple_cmd_token(token))
			ft_lstpush_back(&command, simple_cmd_parse(it));
		else if (token->type == TOKEN_PIPE)
			token_iterator_next(it);
		else
			break ;
	}
	return (command);
}
