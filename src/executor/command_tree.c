/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 18:09:37 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/07 19:39:58 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_execute_io(t_command_tree *left, t_command_tree *right,
		int fd_in, int fd_out)
{
	int	status;
	int	fd[2];

	if (pipe(fd) < 0)
	{
		perror("pipe");
		return (1);
	}
	command_tree_execute_io(left, true, fd_in, fd[1]);
	close(fd[1]);
	status = command_tree_execute_io(right, true, fd[0], fd_out);
	close(fd[0]);
	return (status);
}

int	command_tree_execute_and_io(t_command_tree *ast,
		bool fork_builtin, int fd_in, int fd_out)
{
	int	status;

	status = command_tree_execute_io(ast->left, fork_builtin,
			fd_in, fd_out);
	if (status == 0)
		status = command_tree_execute_io(ast->right, fork_builtin,
				fd_in, fd_out);
	return (status);
}

int	command_tree_execute_or_io(t_command_tree *ast,
		bool fork_builtin, int fd_in, int fd_out)
{
	int	status;

	status = command_tree_execute_io(ast->left, fork_builtin, fd_in, fd_out);
	if (status > 0)
		status = command_tree_execute_io(ast->right, fork_builtin, fd_in, fd_out);
	return (status);
}

int	command_tree_execute_io(t_command_tree *tree, bool fork_builtin,
		int fd_in, int fd_out)
{
	t_ast_item	*item;

	item = tree->item;
	if (item->type == AST_AND)
		return (command_tree_execute_and_io(tree, fork_builtin, fd_in, fd_out));
	if (item->type == AST_OR)
		return (command_tree_execute_or_io(tree, fork_builtin, fd_in, fd_out));
	if (item->type == AST_PIPE)
		return (pipe_execute_io(tree->left, tree->right, fd_in, fd_out));
	if (item->type == AST_CMD)
		return (simple_command_execute_io(item->cmd, fork_builtin,
				fd_in, fd_out));
	if (item->type == AST_PAREN)
		return (command_tree_execute_io(tree->left, true, fd_in, fd_out));
	return (1);
}

int	command_tree_execute(t_command_tree *tree)
{
	return (command_tree_execute_io(tree, false, STDIN_FILENO, STDOUT_FILENO));
}
