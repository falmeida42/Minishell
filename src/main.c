/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:35:11 by falmeida          #+#    #+#             */
/*   Updated: 2021/11/19 00:03:25 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	screening(char **argv)
{
	char	*cmd;
	
	cmd = *argv;
	if (!cmd)
		return (1);
	if (!ft_strcmp(cmd, "exit"))
	{
		g_mini.exit = true;
		return (0);
	}
	if (!ft_strcmp(cmd, "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(cmd, "echo"))
		return (ft_echo());
	if (!ft_strcmp(cmd, "cd"))
		return (ft_cd());
	if(!ft_strcmp(cmd, "env"))
		return (ft_env());
	if(!ft_strcmp(cmd, "export"))
		return (ft_export());
	if (!ft_strcmp(cmd, "unset"))
		return (ft_unset());
	return (ft_exec());
}

int main(int argc, char **argv, char **envp)
{
	char	*input;
	bool	input_empty;

	(void) argc;
	(void) argv;
	g_mini.pid = getpid();
	g_mini.env = map_from_str_array(envp, '=');
	g_mini.exit = false;

	//signal(SIGINT , get_signal);
	//signal(SIGQUIT , get_signal);
	while (42)
	{
		input = readline("minishell: ");
		input_empty = ft_strwc(input, ' ') == 0;
		if (input && !input_empty)
		{
			add_history(input);
			g_mini.argv = ft_split(input, ' ');
			g_mini.status = screening(g_mini.argv);
			free_argv();
		}
		if (input)
			free(input);
		if (g_mini.exit)
		{
			ft_putstr("exit\n");
			break ;
		}
	}
	free_struct();
	return (EXIT_SUCCESS);
}
