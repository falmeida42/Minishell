/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:35:11 by falmeida          #+#    #+#             */
/*   Updated: 2021/12/03 16:36:20 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	g_mini.env = map_from_str_array(envp, '=');
	g_mini.exit = false;
	g_mini.parse_error = NULL;

	//signal(SIGINT , get_signal);
	//signal(SIGQUIT , get_signal);
	while (42)
	{
		g_mini.input = readline("minishell: ");
		g_mini.tree = parser(g_mini.input);
		if (g_mini.parse_error)
		{
			add_history(g_mini.input);
			ft_putendl_error(g_mini.parse_error);
		}
		else if (g_mini.tree)
		{
			add_history(g_mini.input);
			g_mini.status = command_tree_execute(g_mini.tree);
		}
		mini_loop_clear(&g_mini);
		if (g_mini.exit)
		{
			ft_putstr("exit\n");
			break ;
		}
	}
	mini_final_clear(&g_mini);
	return (EXIT_SUCCESS);
}
