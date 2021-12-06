/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:36:00 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/06 11:50:50 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_item	*ast_item_new(t_ast_item_type type)
{
	t_ast_item	*item;

	item = ft_calloc(1, sizeof(*item));
	if (item == NULL)
		return (NULL);
	item->type = type;
	return (item);
}

t_btree	*ast_node_from_token(t_token *token)
{
	t_ast_item	*item;

	if (!token)
		return (NULL);
	item = NULL;
	if (token->type == TOKEN_PIPE)
		item = ast_item_new(AST_PIPE);
	else if (token->type == TOKEN_AND)
		item = ast_item_new(AST_AND);
	else if (token->type == TOKEN_OR)
		item = ast_item_new(AST_OR);
	else if (token->type == TOKEN_LPAREN)
		item = ast_item_new(AST_PAREN);
	if (!item)
		return (NULL);
	return (btree_create_node(item));
}

void	ast_item_free(void *ptr)
{
	t_ast_item	*item;

	item = (t_ast_item *)ptr;
	if (!item)
		return ;
	if (item->type == AST_CMD)
		simple_command_free(item->cmd);
	free(item);
}

void	ast_item_print(void *ptr)
{
	t_ast_item	*item;

	item = (t_ast_item *)ptr;
	ft_putstr("-------------------------------------\n");
	if (item == NULL)
		return ;
	if (item->type == AST_PIPE)
		ft_putstr("PIPE\n");
	else if (item->type == AST_AND)
		ft_putstr("AND\n");
	else if (item->type == AST_OR)
		ft_putstr("OR\n");
	else if (item->type == AST_CMD)
	{
		ft_putstr("SIMPLE COMMAND\n");
		simple_command_print(item->cmd);
	}
}
