/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:36:31 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/25 04:00:56 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_command_free(void *ptr)
{
	t_simple_command	*cmd;

	cmd = (t_simple_command *)ptr;
	ft_lstclear(&cmd->argv, free);
}

void	piped_command_free(void *ptr)
{
	t_piped_command	*command;

	command = (t_piped_command *)ptr;
	ft_lstclear(&command, simple_command_free);
}

void	commands_group_free(void *ptr)
{
	t_commands_group *group;

	group = (t_commands_group *)ptr;
	btree_apply_suffix(group, ast_node_free);
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
	ft_putstr("\nInfile: ");
	ft_putstr(cmd->infile);
	ft_putstr("\nHere doc: ");
	ft_putnbr(cmd->here_doc);
	ft_putstr("\nOutfile: ");
	ft_putstr(cmd->outfile);
	ft_putstr("\nAppend: ");
	ft_putnbr(cmd->append);
	ft_putchar('\n');
}

void	piped_command_print(t_piped_command *command)
{
	int	index;

	index = 0;
	while (command)
	{
		ft_putstr("COMMAND ");
		ft_putnbr(++index);
		ft_putchar('\n');
		simple_command_print(command->content);
		command = command->next;
	}
}
