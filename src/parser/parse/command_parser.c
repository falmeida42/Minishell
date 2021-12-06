/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:35:15 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/02 09:31:21 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_simple_command	*simple_command_parse_redirection_token(
	t_simple_command *cmd, t_token_iterator *it)
{
	t_token			*token;
	t_token_type	type;

	type = token_iterator_peek(it)->type;
	token = token_iterator_next(it);
	if (!is_word_token(token))
		return (clean_exit(cmd, syntax_error_msg(token), simple_command_free));
	if (type == TOKEN_GREATER)
		ft_lstpush_back(&cmd->outfiles, outfile_new(token->value, false));
	else if (type == TOKEN_DGREATER)
		ft_lstpush_back(&cmd->outfiles, outfile_new(token->value, true));
	else if (type == TOKEN_LESS)
		ft_lstpush_back(&cmd->infiles, infile_new(token->value, false));
	else if (type == TOKEN_DLESS)
		ft_lstpush_back(&cmd->infiles, infile_new(token->value, true));
	return (cmd);
}

t_simple_command	*simple_command_parse(t_token_iterator *it)
{
	t_simple_command	*cmd;
	t_token				*token;

	cmd = ft_calloc(1, sizeof(*cmd));
	while (*it)
	{
		token = token_iterator_peek(it);
		if (is_word_token(token))
			ft_lstpush_back(&cmd->argv, ft_strdup(token->value));
		else if (is_redirection_token(token))
		{
			if (!simple_command_parse_redirection_token(cmd, it))
				return (NULL);
		}
		else
			break ;
		token_iterator_next(it);
	}
	return (cmd);
}
