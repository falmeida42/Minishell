/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:36:31 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/08 09:18:11 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_command_free(void *ptr)
{
	t_simple_command	*cmd;

	if (!ptr)
		return ;
	cmd = (t_simple_command *)ptr;
	ft_lstclear(&cmd->argv, free);
	if (cmd->infiles)
		ft_lstclear(&cmd->infiles, infile_free);
	if (cmd->outfiles)
		ft_lstclear(&cmd->outfiles, outfile_free);
	free(cmd);
}

void	command_tree_free(void *ptr)
{
	t_command_tree	*ast;

	ast = (t_command_tree *)ptr;
	btree_clear(ast, ast_item_free);
}

void	simple_command_print(t_simple_command *cmd)
{
	t_list		*lst;

	lst = cmd->argv;
	ft_putstr("Argv: ");
	while (lst)
	{
		ft_putstr(lst->content);
		ft_putchar(' ');
		lst = lst->next;
	}
	ft_putchar('\n');
	lst = cmd->infiles;
	while (lst)
	{
		infile_print(lst->content);
		lst = lst->next;
	}
	lst = cmd->outfiles;
	while (lst)
	{
		outfile_print(lst->content);
		lst = lst->next;
	}
	ft_putchar('\n');
}
