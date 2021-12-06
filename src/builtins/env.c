/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:24:46 by fferreir          #+#    #+#             */
/*   Updated: 2021/12/06 16:58:09 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Reimplementation of the builtin env
 * Prints all the current environment variables
 */
int	ft_env(char **argv, int fd)
{
	(void)argv;
	map_print_fd(g_mini.env, '=', fd);
	return (0);
}
