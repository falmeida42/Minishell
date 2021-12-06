/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:35:15 by falmeida          #+#    #+#             */
/*   Updated: 2021/12/06 17:05:57 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Output the args, separated by spaces, followed by a newline.
 * If -n is specified, the trailing newline is suppressed.
 * The return status is 0 unless a write error occurs. 
 */

void	echo_n_flag(char **argv, int fd)
{
	int	index;

	index = 1;
	if (argv[index] == NULL)
		return ;
	while (argv[index + 1])
	{
		ft_putstr_fd(argv[index], fd);
		ft_putchar_fd(' ', fd);
		++index;
	}
	ft_putstr_fd(argv[index], fd);
}

int	ft_echo(char **argv, int fd)
{
	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
		echo_n_flag(argv + 1, fd);
	else
	{
		echo_n_flag(argv, fd);
		ft_putchar_fd('\n', fd);
	}
	return (0);
}
