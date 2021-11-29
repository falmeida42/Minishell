/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 01:47:24 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/29 12:27:37 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Parses a group of commands within parentheses.
 */
t_command_tree	*command_tree_unwrap_parse(t_token_iterator *it)
{
	t_token			*token;
	t_command_tree	*ast;

	token_iterator_next(it);
	ast = command_tree_parse(it);
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
	return (ast);
}

/*
 * Parses a group of commands (within parenthesis or a piped command)
 */
t_command_tree	*command_tree_node_parse(t_token_iterator *it)
{
	t_token				*token;
	t_ast_node			*node;

	if (!it || !*it)
		return (NULL);
	token = (*it)->content;
	if (token->type == TOKEN_LPAREN)
		return (command_tree_unwrap_parse(it));
	node = ast_node_new(AST_CMD);
	if (!node)
		return (NULL);
	node->cmd = simple_command_parse(it);
	return (btree_create_node(node));
}

/*
 * Parses a group of commands from the right part of a && or || operator.
 * the left part is already parsed and passed as argument (left_ast)
 */
t_command_tree	*command_tree_right_parse(t_token_iterator *it,
						t_command_tree *left_ast)
{
	t_token				*token;
	t_command_tree	*ast;
	t_command_tree	*right_ast;

	token = (*it)->content;
	if (token->type == TOKEN_AND)
		ast = btree_create_node(ast_node_new(AST_AND));
	else if (token->type == TOKEN_OR)
		ast = btree_create_node(ast_node_new(AST_OR));
	else
		return (left_ast);
	token_iterator_next(it);
	right_ast = command_tree_parse(it);
	if (!right_ast)
	{
		btree_apply_suffix(left_ast, ast_node_free);
		return (NULL);
	}
	ast->left = left_ast;
	ast->right = right_ast;
	return (ast);
}

/*
 * Parses a group of commands (with parenthesis or && or || separators)
 */
t_command_tree	*command_tree_parse(t_token_iterator *it)
{
	t_command_tree	*left_ast;

	if (!it || !*it)
		return (NULL);
	left_ast = command_tree_node_parse(it);
	if (!left_ast)
		return (NULL);
	if (!*it)
		return (left_ast);
	return (command_tree_right_parse(it, left_ast));
}

t_command_tree	*parser(char *input)
{
	t_token_list	*token_list;
	t_token_list	*token_it;
	t_command_tree	*ast;
	
	token_list = lex(input);
	// apply expander
	token_it = token_list;
	ast = command_tree_parse(&token_it);
	ft_lstclear(&token_list, token_free);
	return (ast);
}
