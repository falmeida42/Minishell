/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:41:30 by fferreir          #+#    #+#             */
/*   Updated: 2021/12/13 10:00:29 by jceia            ###   ########.fr       */
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

int	ft_strcmp_key(void *ptr1, void *ptr2)
{
	t_pair	*p1;
	t_pair	*p2;

	p1 = (t_pair *)ptr1;
	p2 = (t_pair *)ptr2;
	if (!p1 || !p2)
	{
		ft_putendl_error("Invalid pairs");
		return (0);
	}
	return (ft_strcmp(p1->key, p2->key));
}

// Prints the map to the console.
void	ft_export_no_args(int fd)
{
	t_map	*env;
	t_map	*it;
	t_pair	*p;

	env = ft_lstcopy(g_mini.env);
	ft_lstsort(&env, &ft_strcmp_key);
	it = env;
	while (it)
	{
		p = (t_pair *)it->content;
		if (ft_strcmp(p->key, "_") != 0)
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(p->key, fd);
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(p->value, fd);
			ft_putstr_fd("\"\n", fd);
		}
		it = it->next;
	}
	ft_lstclear(&env, 0);
}

// checks if the key is a valid identifier.
bool	valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '_' && !ft_isalpha(str[i]))
		return (false);
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

/**
 * Reimplementation of the builtin export
 * Adds or edits an environment variable, stored at g_mini.env
 */
int	ft_export(char **argv, int fd)
{
	t_pair	*p;

	if (!argv[1])
	{
		ft_export_no_args(fd);
		return (0);
	}
	while (*(++argv))
	{
		p = pair_from_str(*argv, '=');
		if (!p)
			return (0);
		if (!valid_identifier(p->key))
		{
			ft_putstr_error("export: `");
			ft_putstr_error(*argv);
			ft_putendl_error("': not a valid identifier");
			return (1);
		}
		env_set(p->key, ft_expander(p->value));
		free(p);
	}
	return (0);
}
