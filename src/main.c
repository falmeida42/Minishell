/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:35:11 by falmeida          #+#    #+#             */
/*   Updated: 2021/11/18 14:36:24 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	screening(char *input)
{
	char	*cmd;

	if (g_mini.argv)
	{
		cmd = *g_mini.argv;
		if (!ft_strcmp(cmd, "pwd"))
			ft_pwd();
		else if (!ft_strcmp(cmd, "exit"))
			ft_exit(input);
		else if (!ft_strcmp(cmd, "echo"))
			ft_echo();
		else if (!ft_strcmp(cmd, "cd"))
			ft_cd();
		else if (!ft_strcmp(cmd, " "))
			ft_putchar('\n');
		else if(!ft_strcmp(cmd, "env"))
				ft_env();
		else if(!ft_strcmp(cmd, "export"))
			ft_export();
		else if (!ft_strcmp(cmd, "unset"))
			ft_unset();
		else
			ft_exec();
	}
}

int main(int argc, char **argv, char **envp)
{
	char	*input;

	(void) argc;
	(void) argv;
	g_mini.pid = getpid();
	g_mini.env = map_from_str_array(envp, '=');
	g_mini.exit = false;

	printf("Hello World\n");
	//signal(SIGINT , get_signal);
	//signal(SIGQUIT , get_signal);
	while (42)
	{
		input = readline("minishell: ");
		if (input && ft_strlen(input) != 0)
		{
			add_history(input);
			g_mini.argv = ft_split(input, ' ');
			screening(input);
			free_argv();
			free(input);
		}
		if (g_mini.exit)
			break ;
	}
	free_struct(input);
	return (EXIT_SUCCESS);
}
