/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 03:00:11 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/06 17:07:02 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *name)
{
	if (!ft_strcmp(name, "cd"))
		return (true);
	if (!ft_strcmp(name, "echo"))
		return (true);
	if (!ft_strcmp(name, "env"))
		return (true);
	if (!ft_strcmp(name, "export"))
		return (true);
	if (!ft_strcmp(name, "unset"))
		return (true);
	if (!ft_strcmp(name, "pwd"))
		return (true);
	if (!ft_strcmp(name, "exit"))
		return (true);
	return (false);
}

int	builtin_execute(char **argv, int fd)
{
	if (!ft_strcmp(argv[0], "cd"))
		return (ft_cd(argv, fd));
	if (!ft_strcmp(argv[0], "echo"))
		return (ft_echo(argv, fd));
	if (!ft_strcmp(argv[0], "env"))
		return (ft_env(argv, fd));
	if (!ft_strcmp(argv[0], "export"))
		return (ft_export(argv, fd));
	if (!ft_strcmp(argv[0], "unset"))
		return (ft_unset(argv, fd));
	if (!ft_strcmp(argv[0], "pwd"))
		return (ft_pwd(argv, fd));
	if (!ft_strcmp(argv[0], "exit"))
	{
		g_mini.exit = true;
		return (0);
	}
	return (0);
}

int	builtin_execute_with_fork(char **argv, int fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		status = builtin_execute(argv, fd);
		exit(status);
	}
	else
	{
		waitpid(pid, &status, 0);
		return (status);
	}
}

int	builtin_execute_parent(t_simple_command *cmd, bool do_fork, int fd)
{
	int		status;
	char	**argv;

	set_fd_out_list(cmd->outfiles, &fd);
	argv = ft_lst_to_arr(cmd->argv);
	if (do_fork)
		status = builtin_execute_with_fork(argv, fd);
	else
		status = builtin_execute(argv, fd);
	free(argv);
	return (status);
}
