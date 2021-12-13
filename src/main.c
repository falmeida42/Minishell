/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:35:11 by falmeida          #+#    #+#             */
/*   Updated: 2021/12/13 09:57:49 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <readline/readline.h>

int	minishell_loop(void)
{
	g_mini.tree = parser(g_mini.input);
	if (g_mini.input)
	{
		if (ft_strwc(g_mini.input, ' ') > 0)
			add_history(g_mini.input);
		if (g_mini.parse_error)
			ft_putendl_error(g_mini.parse_error);
		else if (g_mini.tree)
			g_mini.status = command_tree_execute(g_mini.tree);
		mini_loop_clear(&g_mini);
	}
	return (g_mini.status);
}

int	minishell_non_interactive_fd(int fd)
{
	int	status;

	status = 1;
	while (status > 0 && !g_mini.exit)
	{
		status = ft_get_next_line(fd, &g_mini.input);
		minishell_loop();
	}
	if (status < 0)
		return (EXIT_FAILURE);
	return (g_mini.status);
}

int	minishell_non_interactive(char *fname)
{
	int	fd;
	int	status;

	fd = open(fname, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell");
		return (EXIT_FAILURE);
	}
	status = minishell_non_interactive_fd(fd);
	if (close(fd))
	{
		perror("minishell");
		return (EXIT_FAILURE);
	}
	if (status < 0)
		return (EXIT_FAILURE);
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	mini_init(&g_mini, envp);
	if (argc > 1)
		return (minishell_non_interactive(argv[1]));
	signal(SIGINT, get_signal);
	signal(SIGQUIT, get_signal);
	signal(SIGSEGV, get_signal);
	while (!g_mini.exit)
	{
		g_mini.input = readline(g_mini.prompt);
		if (!g_mini.input)
		{
			ft_putendl("exit");
			break ;
		}
		minishell_loop();
	}
	mini_final_clear(&g_mini);
	return (g_mini.status);
}
