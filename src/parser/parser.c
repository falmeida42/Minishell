/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 01:47:24 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/01 16:58:04 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command_tree	*command_tree_parse_split_on(t_token_iterator *it, t_token *token, t_token *end_token)
{
	t_ast_item		*item;
	t_btree			*ast;

	if (!it || !*it)
		return (NULL);
	if (token->type == TOKEN_PIPE)
		item = ast_item_new(AST_PIPE);
	else if (token->type == TOKEN_AND)
		item = ast_item_new(AST_AND);
	else if (token->type == TOKEN_OR)
		item = ast_item_new(AST_OR);
	else
		return (NULL);
	ast = btree_create_node(item);
	if (!ast)
		return (NULL);
	ast->left = command_tree_parse(it, token);
	if (!ast->left)
	{
		btree_apply_suffix(ast, ast_item_free);
		return (NULL);
	}
	token_iterator_next(it);
	ast->right = command_tree_parse(it, end_token);
	if (!ast->right)
	{
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

/*
 * Parses a group of commands (with parenthesis or && or || separators)
 */
t_command_tree	*command_tree_parse(t_token_iterator *it, t_token *end_token)
{
	t_command_tree	*ast;
	t_token			*token;

	if (!it || !*it)
		return (NULL);
	token = (*it)->content;
	if (token->type == TOKEN_AND || token->type == TOKEN_OR || token->type == TOKEN_PIPE)
		return (NULL); // invalid syntax
	token = token_list_lookup_logical(*it, end_token);
	if (token)
		return (command_tree_parse_split_on(it, token, end_token));
	token = token_list_lookup_pipe(*it, end_token);
	if (token)
		return (command_tree_parse_split_on(it, token, end_token));
	token = (*it)->content;
	if (token->type == TOKEN_LPAREN)
	{
		token_iterator_next(it);
		ast = command_tree_parse(it, end_token);
		if (token_iterator_next(it)->type != TOKEN_RPAREN)
			return (NULL);
		return (ast);
	}
	return (command_tree_parse_simple_command(it));
}

void	*expand_operation(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	return (token);
}

char	**lex_and_expand(char *input)
{
	char			**arr;
	int				index;
	int				size;
	t_token			*token;
	t_token_list	*token_list;
	t_token_list	*token_it;

	token_list = lex(input);
	// apply expander
	ft_lstmap(token_list, expand_operation, token_free);
	// convert linked list to array
	size = ft_lstsize(token_list);
	arr = (char **)malloc(sizeof(*arr) * (size + 1));
	if (!arr)
		return (NULL);
	index = 0;
	token_it = token_list;
	while (token_it)
	{
		token = token_it->content;
		arr[index] = ft_strdup(token->value);
		token_it = token_it->next;
		index++;
	}
	arr[size] = NULL;
	ft_lstclear(&token_list, token_free);
	return (arr);
}

t_command_tree	*parser(char *input)
{
	t_token_list	*token_list;
	t_token_list	*token_it;
	t_command_tree	*ast;
	
	token_list = lex(input);
	// apply expander
	token_it = token_list;
	ast = command_tree_parse(&token_it, NULL);
	ft_lstclear(&token_list, token_free);
	return (ast);
}
