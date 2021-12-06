/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:24:23 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/06 11:53:20 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command_tree	*command_tree_parse_split_on(t_token_iterator *it,
		t_token *token, t_token *end_token)
{
	t_btree	*ast;

	if (!it || !*it)
		return (NULL);
	ast = ast_node_from_token(token);
	if (!ast)
		return (NULL);
	ast->left = command_tree_parse(it, token);
	if (!ast->left || token_iterator_peek(it) != token)
	{
		btree_apply_suffix(ast, ast_item_free);
		return (NULL);
	}
	token_iterator_next(it);
	ast->right = command_tree_parse(it, end_token);
	if (!ast->right)
	{
		command_tree_free(ast->left);
		btree_apply_suffix(ast, ast_item_free);
		return (NULL);
	}
	return (ast);
}

t_command_tree	*command_tree_parse_simple_command(t_token_iterator *it)
{
	t_ast_item			*item;

	item = ast_item_new(AST_CMD);
	if (!item)
		return (NULL);
	item->cmd = simple_command_parse(it);
	return (btree_create_node(item));
}

t_command_tree	*command_tree_parse_unwrap_parenthesis(
					t_token_iterator *it, t_token *end_token)
{
	t_command_tree	*ast;
	t_token_list	*lst;

	if (!it || !*it)
		return (NULL);
	ast = ast_node_from_token(token_iterator_peek(it));
	token_iterator_next(it);
	lst = ft_lstprev(*it, end_token);
	if (!lst)
	{
		command_tree_free(ast);
		return (NULL);
	}
	end_token = lst->content;
	if (end_token->type != TOKEN_RPAREN)
	{
		command_tree_free(ast);
		return (NULL);
	}
	ast->left = command_tree_parse(it, end_token);
	if (!ast->left)
	{
		command_tree_free(ast);
		return (NULL);
	}
	if (token_iterator_peek(it) != end_token)
	{
		command_tree_free(ast);
		return (NULL);
	}
	token_iterator_next(it);
	return (ast);
}

/*
 * Parses a group of commands (with parenthesis or && or || separators)
 */
t_command_tree	*command_tree_parse(t_token_iterator *it, t_token *end_token)
{
	t_token			*token;

	if (!it || !*it)
		return (NULL);
	token = token_iterator_peek(it);
	if (token->type == TOKEN_AND || token->type == TOKEN_OR
		|| token->type == TOKEN_PIPE)
		return (NULL);
	token = token_list_lookup_logical(*it, end_token);
	if (token)
		return (command_tree_parse_split_on(it, token, end_token));
	token = token_list_lookup_pipe(*it, end_token);
	if (token)
		return (command_tree_parse_split_on(it, token, end_token));
	token = token_iterator_peek(it);
	if (token->type == TOKEN_LPAREN)
		return (command_tree_parse_unwrap_parenthesis(it, end_token));
	return (command_tree_parse_simple_command(it));
}
