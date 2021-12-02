/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:36:00 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/02 10:05:41 by jpceia           ###   ########.fr       */
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
