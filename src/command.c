/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:36:31 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/02 08:09:37 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_command_free(void *ptr)
{
	t_simple_command	*cmd;

	cmd = (t_simple_command *)ptr;
	ft_lstclear(&cmd->argv, free);
}

void	command_tree_free(void *ptr)
{
	t_command_tree *ast;

	ast = (t_command_tree *)ptr;
	btree_clear(ast, ast_item_free);
}

void	simple_command_print(t_simple_command *cmd)
{
	t_list	*av;

	av = cmd->argv;
	ft_putstr("Argv: ");
	while (av)
	{
		ft_putstr(av->content);
		ft_putchar(' ');
		av = av->next;
	}
	if (cmd->infile)
	{
		ft_putstr("\nInfile: ");
		ft_putstr(cmd->infile);
		ft_putstr("\nHere doc: ");
		ft_putnbr(cmd->here_doc);
	}
	if (cmd->outfile)
	{
		ft_putstr("\nOutfile: ");
		ft_putstr(cmd->outfile);
		ft_putstr("\nAppend: ");
		ft_putnbr(cmd->append);
	}
	ft_putchar('\n');
}
