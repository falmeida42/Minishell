/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:35:42 by falmeida          #+#    #+#             */
/*   Updated: 2021/12/06 16:57:19 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Print the absolute  pathname of the current working directory. 
 * The return status is 0 unless an error occurs while reading the name of the
 * current directory or an invalid option is supplied.
 */

int	ft_pwd(char **argv, int fd)
{
	char	*str;

	(void)argv;
	str = NULL;
	str = getcwd(str, PATH_MAX);
	ft_putendl_fd(str, fd);
	return (0);
}
