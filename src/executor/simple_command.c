/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 02:17:54 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/13 10:12:02 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>

/*
 * In free(argv), the nodes don't need to be free because they're pointers to
 * strings belonging to the simple-cmd struct.
 * Note that this line only runs if execve() fails.
 */
int	exec_child_process(char **argv)
{
	int		status;
	char	*program_name;
	char	**env_arr;

	program_name = normalize_path(*argv);
	if (!program_name)
		return (127);
	env_arr = map_to_str_array(g_mini.env, '=');
	status = execve(program_name, argv, env_arr);
	free(program_name);
	ft_str_array_clear(env_arr, 0);
	return (status);
}

int	simple_command_execute_io_child_process(t_simple_command *cmd,
		int fd_in, int fd_out)
{
	int		status;
	char	**argv;

	set_fd_in_list(cmd->infiles, &fd_in);
	set_fd_out_list(cmd->outfiles, &fd_out);
	if (fd_in != STDIN_FILENO)
		dup2_and_close(fd_in, STDIN_FILENO);
	if (fd_out != STDOUT_FILENO)
		dup2_and_close(fd_out, STDOUT_FILENO);
	argv = ft_lst_to_arr(cmd->argv);
	status = exec_child_process(argv);
	ft_str_array_clear(argv, 0);
	return (status);
}

int	simple_command_execute_io(t_simple_command *cmd, bool fork_builtin,
		int fd_in, int fd_out)
{
	int		status;

	if (!cmd->argv || !cmd->argv->content)
		return (1);
	if (is_builtin(cmd->argv->content))
		return (builtin_execute_parent(cmd, fork_builtin, fd_out));
	g_mini.pid = fork();
	if (g_mini.pid < 0)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	if (g_mini.pid == 0)
	{
		g_mini.is_child = true;
		exit(simple_command_execute_io_child_process(cmd, fd_in, fd_out));
	}
	waitpid(g_mini.pid, &status, 0);
	g_mini.pid = 0;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-WTERMSIG(status));
}

int	simple_command_execute(t_simple_command *cmd)
{
	return (simple_command_execute_io(cmd, false, STDIN_FILENO, STDOUT_FILENO));
}
