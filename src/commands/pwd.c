/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:35:42 by falmeida          #+#    #+#             */
/*   Updated: 2021/11/18 10:53:06 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Print the absolute  pathname of the current working directory. 
 * The return status is 0 unless an error occurs while reading the name of the
 * current directory or an invalid option is supplied.
 */

char	*pwd(void)
{
	char	*str;

	str = NULL;
	str = getcwd(str, PATH_MAX);
	return (str);
}

void	ft_pwd(void)
{
	printf("%s\n", pwd());
}

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
