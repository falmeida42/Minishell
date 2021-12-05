/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:36:31 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/05 00:27:36 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_command_free(void *ptr)
{
	t_simple_command	*cmd;

	cmd = (t_simple_command *)ptr;
	ft_lstclear(&cmd->argv, free);
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfiles)
		ft_lstclear(&cmd->outfiles, outfile_free);
	free(cmd);
}

void	command_tree_free(void *ptr)
{
	t_command_tree *ast;

	ast = (t_command_tree *)ptr;
	btree_clear(ast, ast_item_free);
}

void	simple_command_print(t_simple_command *cmd)
{
	t_list		*lst;
	t_outfile	*out;

	lst = cmd->argv;
	ft_putstr("Argv: ");
	while (lst)
	{
		ft_putstr(lst->content);
		ft_putchar(' ');
		lst = lst->next;
	}
	if (cmd->infile)
	{
		ft_putstr("\nInfile: ");
		ft_putstr(cmd->infile);
		ft_putstr("\nHere doc: ");
		ft_putnbr(cmd->here_doc);
	}
	lst = cmd->outfiles;
	while (lst)
	{
		out = (t_outfile *)(lst->content);
		ft_putstr("\nOutfile: ");
		ft_putstr(out->fname);
		ft_putstr("\nAppend: ");
		ft_putnbr(out->append);
		lst = lst->next;
	}
	ft_putchar('\n');
}
