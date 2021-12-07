/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:52:28 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/18 21:43:43 by jpceia           ###   ########.fr       */
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
	while (c && c == ' ')
		c = char_iterator_next(cursor);
	if (c == '\0')
		return (NULL);
	if (ft_contains(c, "|&><)("))
		return (take_symbol(cursor));
	if (c == '"')
		return (take_dquoted(cursor));
	if (c == '\'')
		return (take_quoted(cursor));
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

/*
int main(int argc, char **argv)
{
	t_token_list *token_list;
	t_token_list *token_it;
	t_token *token;

	if (argc != 2)
	{
		printf("usage: ./lexer <input>\n");
		return (1);
	}
	token_list = lex(argv[1]);
	token_it = token_list;
	while (token_it)
	{
		token = token_it->content;
		printf("%d: %s\n", token->type, token->value);
		token_it = token_it->next;
	}

	token_it = token_list;
	t_commands_group *group = commands_group_parse(&token_it);

	btree_apply_infix(group, print_ast_nodes);
	//command_table_free(table);
	//ft_lstclear(&token_list, token_free);
	return (0);
}
*/