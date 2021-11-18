/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:35:11 by falmeida          #+#    #+#             */
/*   Updated: 2021/11/18 02:08:58 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	screening(char *input)
{
	if (mini.argv)
	{
		if (!ft_strcmp(mini.argv[0], "pwd"))
			ft_pwd();
		else if (!ft_strcmp(mini.argv[0], "exit"))
			ft_exit(input);
		else if (!ft_strcmp(mini.argv[0], "echo"))
			ft_echo();
		else if (!ft_strcmp(mini.argv[0], "cd"))
			ft_cd();
		else if (!ft_strcmp(mini.argv[0], " "))
			ft_putchar('\n');
		else if(!ft_strcmp(mini.argv[0], "env"))
				ft_env();
		else if(!ft_strcmp(mini.argv[0], "export"))
			ft_export();
		else if (!ft_strcmp(mini.argv[0], "unset"))
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
	mini.pid = getpid();
	mini.env = map_from_str_array(envp, '=');
	mini.exit = false;

	//signal(SIGINT , get_signal);
	//signal(SIGQUIT , get_signal);
	while (42)
	{
		input = readline("minishell: ");
		if (input && ft_strlen(input) != 0)
		{
			add_history(input);
			mini.argv = ft_split(input, ' ');
			screening(input);
			free_argv();
			free(input);
			input = NULL;
		}
		if (mini.exit == true)
		{
			free_struct(input);
			ft_lstclear(&mini.env, pair_clear);
			exit(EXIT_SUCCESS);
		}
	}
	return (EXIT_SUCCESS);
}
