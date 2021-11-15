/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:35:11 by falmeida          #+#    #+#             */
/*   Updated: 2021/11/15 20:11:08 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	screening(char *input)
{
	int x = 0;

	// while (mini->argv[++x])
	// 	;
	if (mini.argv)
	{
		if (str_cmp_both_len(mini.argv[0], "pwd"))
			ft_pwd();
		else if (str_cmp_both_len(mini.argv[0], "exit"))
			ft_exit(input);
		else if (str_cmp_both_len(mini.argv[0], "echo"))
			ft_echo();
		else if (str_cmp_both_len(mini.argv[0], "cd"))
			ft_cd();
		else if (str_cmp_both_len(mini.argv[0], " "))
			printf("\n");
		else if(str_cmp_both_len(mini.argv[0], "env"))
				ft_env();
		else if(str_cmp_both_len(mini.argv[0], "export"))
			ft_export();
		else if(str_cmp_both_len(mini.argv[0], "node"))
		{
			if (ft_strlen(mini.argv[1]) > 0)
				ft_envnode_print(mini.env, mini.argv[1]);
		}
		else if (str_cmp_both_len(mini.argv[0], "unset"))
		{
			if (x > 1)
				ft_unset();
		}
		else
			ft_ls();
	}
	else
		return ;
}

int main(int argc, char **argv, char **env)
{

	char	*input;

	(void) argc;
	(void) argv;
	mini.head = malloc(sizeof(t_env));
	mini.pid = getpid();
	mini.env = get_env(env);
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
			free_env(mini.env);
			exit(0);
		}
	}
	return (0);
}
