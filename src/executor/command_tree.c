/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 18:09:37 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/01 18:39:30 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pipe_execute_io(t_command_tree *left, t_command_tree *right, int io[2])
{
    int fd[2];
    int io_left[2];
    int io_right[2];

	if (pipe(fd) < 0)
	{
        ft_putstr_error("Error creating pipes\n");
        return (1);
	}
    io_left[0] = io[0];
    io_left[1] = fd[0];
    io_right[0] = fd[1];
    io_right[1] = io[1];
    command_tree_execute_io(left, io_left);
    return (command_tree_execute_io(right, io_right));
}

int command_tree_execute_io(t_command_tree *tree, int fd[2])
{
    int         status;
    t_ast_item  *item;

    item = tree->item;
	status = 1;
    if (item->type == AST_AND)
    {
        status = command_tree_execute_io(tree->left, fd);
		if (status == 0)
			status = command_tree_execute_io(tree->right, fd);
    }
    else if (item->type == AST_OR)
    {
        status = command_tree_execute_io(tree->left, fd);
		if (status > 0)
			status = command_tree_execute_io(tree->right, fd);
    }
    else if (item->type == AST_PIPE)
    {
		return (pipe_execute_io(tree->left, tree->right, fd));
    }
    else if (item->type == AST_CMD)
    {
        return (simple_command_execute_io(item->cmd, fd));
    }
    return (status);
}

int command_tree_execute(t_command_tree *tree)
{
    int         fd[2];

    fd[0] = STDIN_FILENO;
    fd[1] = STDOUT_FILENO;
    return (command_tree_execute_io(tree, fd));
}
