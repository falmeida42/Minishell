/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 02:17:54 by jpceia            #+#    #+#             */
/*   Updated: 2021/12/01 18:35:14 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>

void	update_io(t_simple_command *cmd, int *fd_in, int *fd_out)
{
	if (cmd->infile)
	{
		*fd_in = open(cmd->infile, O_RDONLY);
		if (*fd_in < 0)
		{
			perror(cmd->infile);
			exit(EXIT_FAILURE);
		}
	}
	if (cmd->outfile)
	{
		// replace or append?
		if (cmd->append)
			*fd_out = open(cmd->outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			*fd_out = open(cmd->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (*fd_out < 0)
		{
			perror(cmd->outfile);
			exit(EXIT_FAILURE);
		}
	}
}

void set_io(int fd[2])
{
	if (dup2(fd[0], STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd[1], STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}

void restore_io(int fd[2])
{
	if (dup2(fd[0], STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd[1], STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	close(fd[1]);
}	


int simple_command_child_process(char **argv)
{
	char	*program_name;
	char	**env_arr;
	
	program_name = normalize_path(*argv);
	env_arr = map_to_str_array(g_mini.env, '=');
	execve(program_name, argv, env_arr);
	free(argv); // the nodes don't need to be free because they're pointers to strings belonging to the simple-cmd struct
	free(program_name);
	ft_str_array_clear(env_arr, 0);
	return (EXIT_FAILURE);
}

void set_fd_out(char *fname, bool append, int *old, int *new)
{
	if (fname)
	{
		if (*old)
			*old = dup(STDOUT_FILENO);
		if (append)
			*new = open(fname, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			*new = open(fname, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (*new < 0)
		{
			perror(fname);
			exit(EXIT_FAILURE);
		}
		dup2(*new, STDOUT_FILENO);
		close(*new);
	}
}

void set_fd_in(char *fname, int *old, int *new)
{
	if (fname)
	{
		if (*old)
			*old = dup(STDIN_FILENO);
		*new = open(fname, O_RDONLY);
		if (*new < 0)
		{
			perror(fname);
			exit(EXIT_FAILURE);
		}
		dup2(*new, STDIN_FILENO);
		close(*new);
	}
}


int builtin_execute_io(t_simple_command *cmd, int io[2])
{
	int		status;
	int		bak;
	int		fd_out;
	char	**argv;
	
	fd_out = io[1];
	set_fd_out(cmd->outfile, cmd->append, &bak, &fd_out);
	argv = ft_lst_to_arr(cmd->argv);
	status = builtin_execute(argv);
	ft_str_array_clear(argv, 0);
	if (cmd->outfile)
	{
		dup2(bak, STDOUT_FILENO);
		close(bak);
	}
	return (status);
}

int simple_command_execute_io(t_simple_command *cmd, int io[2])
{
	char	**argv;
	int		status;
	pid_t   pid;
	
	if (!cmd->argv || !cmd->argv->content)
		return (0);
	if (is_builtin(cmd->argv->content))
		return (builtin_execute_io(cmd, io));
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		set_fd_in(cmd->infile, NULL, &io[0]);
		set_fd_out(cmd->outfile, cmd->append, NULL, &io[1]);
		argv = ft_lst_to_arr(cmd->argv);
		status = simple_command_child_process(argv);
		ft_str_array_clear(argv, 0);
		free_struct();
		exit(status);
	}
	waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (-WTERMSIG(status));
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
		simple_command_child_process(argv);
	waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (-WTERMSIG(status));
}
