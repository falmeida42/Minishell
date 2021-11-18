/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 01:47:24 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/18 21:13:24 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands_group	*commands_group_node_parse(t_token_iterator *it)
{
	t_token				*token;
	t_ast_node			*node;
	t_commands_group	*ast;

	if (!it || !*it)
		return (NULL);
	token = (*it)->content;
	if (token->type == TOKEN_LPAREN)
	{
		token_iterator_next(it);
		ast = commands_group_parse(it);
		if (!ast)
			return (NULL);
		token = (*it)->content;
		if (!*it || token->type != TOKEN_RPAREN)
		{
			btree_apply_suffix(ast, ast_node_free);
			ft_putstr_error("syntax error: unclosed parenthesis\n");
			return (NULL);
		}
		token_iterator_next(it);
	}
	else
	{
		node = ast_node_new(AST_CMD);
		if (!node)
			return (NULL);
		node->command = command_parse(it);
		ast = btree_create_node(node);
	}
	return (ast);
}

t_commands_group	*commands_group_parse(t_token_iterator *it)
{
	t_token				*token;
	t_commands_group	*ast;
	t_commands_group	*left_ast;
	t_commands_group	*right_ast;

	if (!it || !*it)
		return (NULL);
	left_ast = commands_group_node_parse(it);
	if (!left_ast)
		return (NULL);
	if (!*it)
		return (left_ast);
	token = (*it)->content;
	if (token->type == TOKEN_AND)
		ast = btree_create_node(ast_node_new(AST_AND));
	else if (token->type == TOKEN_OR)
		ast = btree_create_node(ast_node_new(AST_OR));
	else
		return left_ast;
	token_iterator_next(it);
	right_ast = commands_group_parse(it);
	if (!right_ast)
	{
		btree_apply_suffix(left_ast, ast_node_free);
		return (NULL);
	}
	ast->left = left_ast;
	ast->right = right_ast;
	return (ast);
}