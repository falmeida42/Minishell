/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:00:45 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/18 11:00:56 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Cause the shell to exit with a status of n.
 * If n is omitted, the exit status is that of the last command executed.
 * A trap on EXIT is executed before the shell terminates.
 */
void	ft_exit(char *input)
{
	free_struct(input);
	g_mini.exit = true;
	ft_putstr("exit\n");
	// kill(g_mini.pid, SIGINT);
}
