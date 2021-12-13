/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 09:52:09 by jceia             #+#    #+#             */
/*   Updated: 2021/12/13 09:59:56 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_issignal(char c)
{
	return (c == '+' || c == '-');
}

bool	check_if_numeric(char *str)
{
	int	i;

	i = 0;
	if (ft_issignal(str[i]))
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_ptrlen(char **argv)
{
	int	len;

	len = 0;
	while (argv[len])
		len++;
	return (len);
}

int	ft_exit_one_arg(char *str_code)
{
	g_mini.exit = true;
	if (!check_if_numeric(str_code))
	{
		ft_putstr_error("exit: ");
		ft_putstr_error(str_code);
		ft_putendl_error(": numeric argument required");
		return (255);
	}
	return (ft_atoi(str_code));
}

int	ft_exit(char **argv, int fd)
{
	int	len;

	(void)fd;
	len = ft_ptrlen(argv);
	if (!g_mini.is_child && len <= 2)
		ft_putendl_error("exit");
	if (len == 1)
	{
		g_mini.exit = true;
		return (0);
	}
	else if (len == 2)
		return (ft_exit_one_arg(argv[1]));
	ft_putendl_error("logout");
	ft_putendl_error("exit: too many arguments");
	return (1);
}
