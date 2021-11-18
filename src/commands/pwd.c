/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:35:42 by falmeida          #+#    #+#             */
/*   Updated: 2021/11/18 11:00:41 by jpceia           ###   ########.fr       */
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
