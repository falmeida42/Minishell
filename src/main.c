/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:35:11 by falmeida          #+#    #+#             */
/*   Updated: 2021/09/07 17:45:21 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	screening(t_mini *mini)
{
	if (mini->argv)
	{
		if (!ft_strncmp(mini->argv[0], "pwd", ft_strlen(mini->argv[0])))
			ft_pwd();
		else if (!ft_strncmp(mini->argv[0], "exit", ft_strlen(mini->argv[0])))
			ft_exit(mini->pid);
		else if (!ft_strncmp(mini->argv[0], "echo", ft_strlen(mini->argv[0])))
			ft_echo(mini->argv);
		else if (!ft_strncmp(mini->argv[0], "cd", ft_strlen(mini->argv[0])))
			ft_cd(mini);
		else if (!ft_strncmp(mini->argv[0], " ", ft_strlen(mini->argv[0])))
			printf("\n");
		else if(!ft_strncmp(mini->argv[0], "env", ft_strlen(mini->argv[0])))
			ft_env(mini);
		else if(!ft_strncmp(mini->argv[0], "export", ft_strlen(mini->argv[0])))
			ft_export(mini);
		else if(!ft_strncmp(mini->argv[0], "node", ft_strlen(mini->argv[0])))
		{
			if (ft_strlen(mini->argv[1]) > 0)
				ft_lstnode_print(mini->env, mini->argv[1]);
		}
		else if (!ft_strncmp(mini->argv[0], "unset", ft_strlen(mini->argv[0])))
		{
			if (ft_strlen(mini->argv[1]) > 0)
				ft_unset(mini);
		}
		else
			ft_ls(mini);
	}
	else
		return ;
}

void	get_signal(int signal)
{
	if (signal == SIGHUP)
		return ;
}

int main(int argc, char **argv, char **env)
{
	t_mini	mini;
	char	*input;

	(void) argc;
	(void) argv;
	mini.pid = getpid();
	mini.env = get_env(env, &mini);
	while (42)
	{
		input = readline("minishell: ");
		if (ft_strlen(input) > 0)
		{
			signal(mini.pid, get_signal);
			add_history(input);
			mini.argv = ft_split(input, ' ');
			screening(&mini);
		}
	}
	return (0);
}
