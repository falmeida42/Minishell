/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 03:00:11 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/04 22:04:04 by jpceia           ###   ########.fr       */
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

int	builtin_execute(char **argv)
{
	if (!ft_strcmp(argv[0], "cd"))
		return (ft_cd(argv));
	if (!ft_strcmp(argv[0], "echo"))
		return (ft_echo(argv));
	if (!ft_strcmp(argv[0], "env"))
		return (ft_env(argv));
	if (!ft_strcmp(argv[0], "export"))
		return (ft_export(argv));
	if (!ft_strcmp(argv[0], "unset"))
		return (ft_unset(argv));
	if (!ft_strcmp(argv[0], "pwd"))
		return (ft_pwd(argv));
	if (!ft_strcmp(argv[0], "exit"))
	{
		g_mini.exit = true;
		return (0);
	}
	return (0);
}

int builtin_execute_with_fork(char **argv)
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
		//dup2(fd_out, STDOUT_FILENO);
		status = builtin_execute(argv);
		//free(argv);
		exit(status);
	}
	else
	{
		waitpid(pid, &status, 0);
		return (status);
	}
}

int	builtin_execute_fd(t_simple_command *cmd, bool do_fork, int fd_out)
{
	int		status;
	int		bak;
	char	**argv;

	set_fd_out_list(cmd->outfiles, &fd_out);
	if (fd_out != STDOUT_FILENO)
	{
		bak = dup(STDOUT_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	argv = ft_lst_to_arr(cmd->argv);
	if (do_fork)
		status = builtin_execute_with_fork(argv);
	else
		status = builtin_execute(argv);
	if (fd_out != STDOUT_FILENO)
	{
		dup2(bak, STDOUT_FILENO);
		close(bak);
	}
	free(argv);
	return (status);
}
