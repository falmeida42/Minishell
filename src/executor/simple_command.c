/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 02:17:54 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/03 09:33:07 by jpceia           ###   ########.fr       */
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
int exec_child_process(char **argv)
{
	int 	status;
	char	*program_name;
	char	**env_arr;
	
	program_name = normalize_path(*argv);
	if (!program_name)
		return (127);
	env_arr = map_to_str_array(g_mini.env, '=');
	status = execve(program_name, argv, env_arr);
	free(argv);
	free(program_name);
	ft_str_array_clear(env_arr, 0);
	return (status);
}

int	simple_command_execute_io_child_process(t_simple_command *cmd,
		int fd_in, int fd_out)
{
	int 	status;
	char	**argv;
	
	set_fd_in(cmd->infile, NULL, &fd_in);
	set_fd_out(cmd->outfile, cmd->append, NULL, &fd_out);
	argv = ft_lst_to_arr(cmd->argv);
	status = exec_child_process(argv);
	ft_str_array_clear(argv, 0);
	free_struct();
	exit(status);
}

int simple_command_execute_io(t_simple_command *cmd, int fd_in, int fd_out)
{
	int		status;
	pid_t   pid;
	
	if (!cmd->argv || !cmd->argv->content)
		return (1);
	if (is_builtin(cmd->argv->content))
		return (builtin_execute_fd(cmd, fd_out));
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	if (pid == 0)
		simple_command_execute_io_child_process(cmd, fd_in, fd_out);
	waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (-WTERMSIG(status));
}

int simple_command_execute(t_simple_command *cmd)
{
	return (simple_command_execute_io(cmd, STDIN_FILENO, STDOUT_FILENO));
}

int	ft_exec(char **argv)
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
		exec_child_process(argv);
	waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (-WTERMSIG(status));
}
