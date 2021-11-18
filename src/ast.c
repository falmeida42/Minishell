/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:36:00 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/18 21:44:39 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*ast_node_new(t_ast_node_type type)
{
	t_ast_node	*node;

	node = ft_calloc(1, sizeof(*node));
	if (node == NULL)
		return (NULL);
	node->type = type;
	return (node);
}

void	ast_node_free(void *ptr)
{
	t_ast_node	*node;

	node = (t_ast_node *)ptr;
	if (!node)
		return ;
	if (node->type == AST_CMD)
		command_free(node->command);
	free(node);
}

void	ast_node_print(void *ptr)
{
	t_ast_node	*node;

	node = (t_ast_node *)ptr;
	if (node == NULL)
		return ;
	if (node->type == AST_AND)
		ft_putstr("AST_AND\n");
	else if (node->type == AST_OR)
		ft_putstr("AST_OR\n");
	else if (node->type == AST_CMD)
	{
		ft_putstr("AST_CMD\n");
		command_print(node->command);
	}
}
