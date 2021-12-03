/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:41:30 by fferreir          #+#    #+#             */
/*   Updated: 2021/12/03 18:35:01 by jpceia           ###   ########.fr       */
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

// Prints the map to the console.
void	ft_export_no_args(void)
{
	t_map	*it;
	t_pair	*p;

	it = g_mini.env;
	while (it)
	{
		p = (t_pair *)it->content;
		ft_putstr("declare -x ");
		ft_putstr(p->key);
		ft_putstr("=\"");
		ft_putstr(p->value);
		ft_putstr("\"\n");
		it = it->next;
	}
}

/**
 * Reimplementation of the builtin export
 * Adds or edits an environment variable, stored at g_mini.env
 */
int	ft_export(char **argv)
{
	t_pair	*p;

	if (!argv[1])
	{
		ft_export_no_args();
		return (0);
	}
	while(*(++argv))
	{
		p = pair_from_str(*argv, '=');
		if (!p)
			return (1);
		env_set(p->key, p->value);
		free(p);	
	}
	return (0);
}
