/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 01:47:24 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/29 16:04:36 by jceia            ###   ########.fr       */
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
	int					parent_count;
	t_token_list		*tmp;
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
	tmp = *it;
	while (tmp)
	{
		token = *tmp;
		if (token->type == TOKEN_LPAREN)
			parent_count++;
		else if (token->type == TOKEN_RPAREN)
			parent_count--;
		else if (token->type == TOKEN_AND || token->type == TOKEN_AND)
		{
			if (parent_count == 0)
				break ;
		}
		tmp = tmp->next;
	}
	// if breaks in logical operator
	if (token->type == TOKEN_AND || token->type == TOKEN_AND)
	// else 
	if (token->type)
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


t_command_tree	*command_tree_parse_split_on(t_token_iterator *it, t_token *token, t_token *eot)
{
	t_token_type	type;
	t_ast_node	*node;

	if (!it || !*it)
		return (NULL);
	type = token->type;
	if (type ==)
		node = ast_node_new();
}

t_token	*token_list_lookup_logical(t_token_list *lst)
{
	int		parent_count;
	t_token	*token;

	parent_count = 0;
	while (lst)
	{
		token = (t_token *)lst->content;
		if (token->type == TOKEN_LPAREN)
			parent_count++;
		else if (token->type == TOKEN_RPAREN)
			parent_count--;
		else if (token->type == TOKEN_AND || token->type == TOKEN_OR
			|| parent_count == 0)
			return (token);
		lst = lst->next;
	}
	return (NULL);
}

t_token	*token_list_lookup_pipe(t_token_list *lst)
{
	int		parent_count;
	t_token	*token;

	parent_count = 0;
	while (lst)
	{
		token = (t_token *)lst->content;
		if (token->type == TOKEN_LPAREN)
			parent_count++;
		else if (token->type == TOKEN_RPAREN)
			parent_count--;
		else if (token->type == TOKEN_PIPE && parent_count == 0)
			return (token);
		lst = lst->next;
	}
	return (NULL);
}

t_command_tree	*command_tree_parse_simple_command(t_token_list *it)
{
	t_ast_node			*ast;
	
	ast = ast_node_new(AST_CMD);
	if (!ast)
		return (NULL);
	ast->cmd = simple_command_parse(it);
	return (btree_create_node(ast));
}

/*
 * Parses a group of commands (with parenthesis or && or || separators)
 */
t_command_tree	*command_tree_parse_until(t_token_list *it, t_token *eot)
{
	t_token				*token;

	if (!it || !*it)
		return (NULL);
	token = (*it)->content;
	if (token->type == TOKEN_AND || token->type == TOKEN_OR || token->type == TOKEN_PIPE)
		return (NULL); // invalid syntax
	token = token_list_lookup_logical(*it, eot);
	if (token)
		return (command_tree_parse_split_on(it, token, eot));
	token = token_list_lookup_pipe(*it);
	if (token)
		return (command_tree_parse_split_on(it, token, eot));
	token = (*it)->content;
	if (token->type == TOKEN_LPAREN)
	{
		token_iterator_next(it);
		return (command_tree_parse(it));
	}
	return (command_tree_parse_simple_command(it));
}

t_command_tree	*parser(char *input)
{
	t_token_list	*token_list;
	t_token_list	*token_it;
	t_command_tree	*ast;
	
	token_list = lex(input);
	// apply expander
	token_it = token_list;
	ast = command_tree_parse_until(token_it, NULL);
	ft_lstclear(&token_list, token_free);
	return (ast);
}
