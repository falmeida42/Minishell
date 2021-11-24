/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:35:15 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/24 22:48:30 by jpceia           ###   ########.fr       */
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

bool	piped_command_parse_step(t_token_iterator *it, t_piped_command **command)
{
	t_token		*token;
	static bool	prev_pipe = true;

	token = (*it)->content;
	if (is_simple_command_token(token))
	{
		ft_lstpush_back(command, simple_command_parse(it));
		prev_pipe = false;
		return (true);
	}
	else if (token->type == TOKEN_PIPE)
	{
		if (prev_pipe)
		{
			piped_command_free(*command);
			*command = NULL;
			ft_putstr_error("syntax error near unexpected token '|'\n");
			return (false);
		}
		token_iterator_next(it);
		prev_pipe = true;
		return (true);
	}
	return (false);
}

t_piped_command	*piped_command_parse(t_token_iterator *it)
{
	t_piped_command	*command;
	bool			do_continue;

	command = NULL;
	do_continue = true;
	while (*it && do_continue)
		do_continue = piped_command_parse_step(it, &command);
	return (command);
}
