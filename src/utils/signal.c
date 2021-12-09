/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:00:13 by falmeida          #+#    #+#             */
/*   Updated: 2021/12/09 14:47:28 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(void)
{
	ft_putchar('\n');
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_mini.pid)
	{
		ft_putstr("^C\n");
		g_mini.status = 130;
	}
	else
	{
		g_mini.status = 1;
		rl_redisplay();
	}
}

void	handle_sigquit(void)
{
	if (g_mini.pid)
	{
		ft_putstr("^\\Quit: 3\n");
		g_mini.status = 131;
		rl_redisplay();
	}
	else
	{
		ft_putstr(g_mini.prompt);
		ft_putstr(rl_line_buffer);
	}
}

void	get_signal(int signal)
{
	if (signal == SIGINT)
		handle_sigint();
	else if (signal == SIGQUIT)
		handle_sigquit();
}
