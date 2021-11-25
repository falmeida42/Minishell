/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:35:11 by falmeida          #+#    #+#             */
/*   Updated: 2021/11/25 06:26:26 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"


int main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**args;
	bool	input_empty;

	(void) argc;
	(void) argv;
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
			args = ft_split(input, ' ');
			if (is_builtin(args[0]))
				g_mini.status = builtin_execute(args);
			else
				g_mini.status = ft_exec(args);
			ft_str_array_clear(args, 0);
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
