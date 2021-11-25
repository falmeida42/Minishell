/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 03:00:11 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/25 03:56:12 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *name)
{
	if (!ft_strcmp(name, "cd"))
		return true;
	if (!ft_strcmp(name, "echo"))
		return true;
	if (!ft_strcmp(name, "env"))
		return true;
	if (!ft_strcmp(name, "export"))
		return true;
	if (!ft_strcmp(name, "unset"))
		return true;
	if (!ft_strcmp(name, "pwd"))
		return true;
	if (!ft_strcmp(name, "exit"))
		return true;
	return false;
}

int	builtin_execute(char **argv)
{
	if (!ft_strcmp(argv[0], "cd"))
		return ft_cd(argv);
	if (!ft_strcmp(argv[0], "echo"))
		return ft_echo(argv);
	if (!ft_strcmp(argv[0], "env"))
		return ft_env(argv);
	if (!ft_strcmp(argv[0], "export"))
		return ft_export(argv);
	if (!ft_strcmp(argv[0], "unset"))
		return ft_unset(argv);
	if (!ft_strcmp(argv[0], "pwd"))
		return ft_pwd(argv);
	if (!ft_strcmp(argv[0], "exit"))
	{
		g_mini.exit = true;
		return (0);
	}
	return (0);
}
