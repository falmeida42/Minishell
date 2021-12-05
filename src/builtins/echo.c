/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:35:15 by falmeida          #+#    #+#             */
/*   Updated: 2021/12/04 16:03:44 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Output the args, separated by spaces, followed by a newline.
 * If -n is specified, the trailing newline is suppressed.
 * The return status is 0 unless a write error occurs. 
 */

void	echo_n_flag(char **argv)
{
	int	index;

	index = 1;
	if (argv[index] == NULL)
		return ;
	while (argv[index + 1])
	{
		ft_putstr(argv[index]);
		ft_putchar(' ');
		++index;
	}
	ft_putstr(argv[index]);
}

int	ft_echo(char **argv)
{
	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
		echo_n_flag(argv + 1);
	else
	{
		echo_n_flag(argv);
		ft_putchar('\n');
	}
	return (0);
}
