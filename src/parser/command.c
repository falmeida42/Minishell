/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:36:31 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/16 15:11:46 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	simple_cmd_free(void *ptr)
{
	t_simple_cmd	*cmd;

	cmd = (t_simple_cmd *)ptr;
	ft_lstclear(&cmd->argv, NULL);
}

void	simple_cmd_print(t_simple_cmd *cmd)
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

void	command_print(t_command *command)
{
	int	index;

	index = 0;
	while (command)
	{
		ft_putstr("COMMAND ");
		ft_putnbr(++index);
		ft_putchar('\n');
		simple_cmd_print(command->content);
		command = command->next;
	}
}
