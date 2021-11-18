/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:35:15 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/18 21:13:10 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_command_parse_redirection_token(
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

t_simple_command	*simple_command_parse(t_token_iterator *it)
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
			simple_command_parse_redirection_token(cmd, it);
		else
			break ;
		token_iterator_next(it);
	}
	return (cmd);
}

t_command	*command_parse(t_token_iterator *it)
{
	t_token			*token;
	t_command		*command;
	bool			prev_pipe;

	command = NULL;
	prev_pipe = true;
	while (*it)
	{
		token = (*it)->content;
		if (is_simple_command_token(token))
		{
			ft_lstpush_back(&command, simple_command_parse(it));
			prev_pipe = false;
		}
		else if (token->type == TOKEN_PIPE)
		{
			if (prev_pipe)
			{
				command_free(command);
				ft_putstr_error("syntax error near unexpected token '|'\n");
				return (NULL);
			}
			token_iterator_next(it);
			prev_pipe = true;
		}
		else
			break ;
	}
	return (command);
}
