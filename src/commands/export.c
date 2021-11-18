/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:41:30 by fferreir          #+#    #+#             */
/*   Updated: 2021/11/18 03:07:23 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The supplied names are marked for automatic export to the environment of
 * subsequently executed commands. If no names are given a list of names of all
 * exported variables is printed. If a variable name is followed by =word,
 * the value of the variable is set to word.
 * 
 * export returns an exit status of 0 unless an invalid option is encountered,
 * one of the names is not a valid shell variable name.
 */

/**
 * Reimplementation of the builtin export
 * Adds or edits an environment variable, stored at g_mini.env
 */
int	ft_export(void)
{
	char	*arg;
	t_pair	*p;

	arg = g_mini.argv[1];
	if (arg == NULL)
		return (1);
	p = pair_from_str(arg, '=');
	if (!p)
		return (1);
	env_set(p->key, p->value);
	free(p);
	return (0);
}
